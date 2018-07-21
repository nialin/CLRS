#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define UNSUCCESS	(0)
#define SUCCESS		(1)

#define GET_FROM_FUNC	(0)
#define GET_FROM_STDIN	(1)


typedef int status;

struct object {
	int primary_key, foreign_key;
	char discription[10];
};

struct tab_node {
	struct object *site_data;
	struct tab_node *next;
};

struct hash_table {
	struct tab_node *head[17];
};


int hash_func_division(int primary_key);

void hash_table_init(struct hash_table *table);
void hash_table_destroy(struct hash_table *table);

status hash_table_insert(struct hash_table *table, int primary_key, struct object *obj);
status hash_table_delete(struct hash_table *table, int primary_key, struct object *obj);
status hash_table_search(struct hash_table *table, int primary_key, struct object *obj);


int hash_func_division(int primary_key)
{
	return primary_key % 17;
}

void hash_table_init(struct hash_table *table)
{
	memset(table->head, 0, sizeof(struct tab_node *[17]));
}

void hash_table_destroy(struct hash_table *table)
{
	int i;
	struct tab_node *ptr, *del_node;

	for(i = 0; i < 17; ++i) {
		for(ptr = table->head[i]; ptr; ) {
			del_node = ptr;
			ptr = ptr->next;

			free(del_node->site_data);
			free(del_node);
		}
	}
}

status hash_table_insert(struct hash_table *table, int primary_key, struct object *obj)
{
	int index;
	struct tab_node *ptr, *new_node;
	struct object *new_obj;

	index = hash_func_division(primary_key);

	for(ptr = table->head[index]; ptr && ptr->site_data->primary_key != primary_key; ptr = ptr->next)
		;

	if(ptr)
		return UNSUCCESS;

	if(!(new_obj = malloc(sizeof(struct object))))
		exit(ENOMEM);

	memcpy(new_obj, obj, sizeof(struct object));

	if(!(new_node = malloc(sizeof(struct tab_node))))
		exit(ENOMEM);

	new_node->site_data = new_obj;
	new_node->next = NULL;

	if(table->head[index])
		new_node->next = table->head[index];

	table->head[index] = new_node;

	return SUCCESS;
}

status hash_table_delete(struct hash_table *table, int primary_key, struct object *obj)
{
	int index;
	struct tab_node **ptr, *del_node;

	index = hash_func_division(primary_key);

	for(ptr = &table->head[index]; *ptr && (*ptr)->site_data->primary_key != primary_key; ptr = &(*ptr)->next)
		;

	if(!*ptr)
		return UNSUCCESS;

	memcpy(obj, (*ptr)->site_data, sizeof(struct object));

	del_node = *ptr;
	*ptr = (*ptr)->next;
	free(del_node);

	return SUCCESS;
}

status hash_table_search(struct hash_table *table, int primary_key, struct object *obj)
{
	int index;
	struct tab_node *ptr;

	index = hash_func_division(primary_key);

	for(ptr = table->head[index]; ptr && ptr->site_data->primary_key != primary_key; ptr = ptr->next)
		;

	if(!ptr)
		return UNSUCCESS;

	memcpy(obj, ptr->site_data, sizeof(struct object));

	return SUCCESS;
}

int main(int argc, char *argv[])
{
	int primary_key;
	struct object container;
	struct hash_table table;

	int choice;
	struct func_info {
		char *discription;
		int get_flg;
		status (*func)(struct hash_table *, int, struct object *);
	} func_table[] = {
		{ "Exit"	, GET_FROM_FUNC	, 	NULL				},
		{ "Insert"	, GET_FROM_STDIN, 	hash_table_insert	},
		{ "Delete"	, GET_FROM_FUNC	,	hash_table_delete	},
		{ "Search"	, GET_FROM_FUNC	,	hash_table_search	}
	};

	hash_table_init(&table);

	do {
		scanf("%d", &choice);

		if(choice <= 0 || choice >= sizeof(func_table) / sizeof(func_table[0]))
			continue;

		scanf("%d", &primary_key);

		if(GET_FROM_STDIN == func_table[choice].get_flg) {
			container.primary_key = primary_key;
			scanf("%d%s", &container.foreign_key, container.discription);
		}

		if(SUCCESS == func_table[choice].func(&table, primary_key, &container))
			printf("%s {[%d], %d, %s} success.\n", func_table[choice].discription,
					container.primary_key, container.foreign_key, container.discription);
		else
			printf("%s {[%d]} unsuccess.\n", func_table[choice].discription, primary_key);

	}while(choice);

	hash_table_destroy(&table);

	return EXIT_SUCCESS;
}
