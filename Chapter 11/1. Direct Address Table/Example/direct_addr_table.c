#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SUCCESS		(0)
#define UNSUCCESS	(1)

#define GET_FROM_FUNC	(0)
#define GET_FROM_STDIN	(1)


typedef int status;

struct tab_node {
	int foreign_key;
	char discription[10];
};

struct direct_addr_table {
	int up_range, down_range;
	struct tab_node **nodes;
};


status direct_addr_init(struct direct_addr_table *table);
status direct_addr_exit(struct direct_addr_table *table);

status direct_addr_insert(struct direct_addr_table *table, int primary_key, struct tab_node *elem);
status direct_addr_delete(struct direct_addr_table *table, int primary_key, struct tab_node *elem);
status direct_addr_search(struct direct_addr_table *table, int primary_key, struct tab_node *elem);


status direct_addr_init(struct direct_addr_table *table)
{
	scanf("%d%d", &table->down_range, &table->up_range);

	if(table->down_range > table->up_range)
		return UNSUCCESS;

	if(!(table->nodes = malloc((table->up_range - table->down_range + 1) * sizeof(struct tab_node *))))
		exit(ENOMEM);

	memset(table->nodes, 0, (table->up_range - table->down_range + 1) * sizeof(struct tab_node *));

	return SUCCESS;
}

status direct_addr_exit(struct direct_addr_table *table)
{
	int i;

	if(!table->nodes)
		return UNSUCCESS;

	for(i = 0; i <= table->up_range - table->down_range; ++i) {
		if(table->nodes[i]) {
			free(table->nodes[i]);
			table->nodes[i] = NULL;
		}
	}

	free(table->nodes);
	table->nodes = NULL;

	return SUCCESS;
}

status direct_addr_insert(struct direct_addr_table *table, int primary_key, struct tab_node *elem)
{
	struct tab_node *new_node;

	if(primary_key < table->down_range || primary_key > table->up_range ||
			table->nodes[primary_key - table->down_range])
		return UNSUCCESS;

	if(!(new_node = malloc(sizeof(struct tab_node))))
		exit(ENOMEM);

	table->nodes[primary_key - table->down_range] = new_node;
	memcpy(new_node, elem, sizeof(struct tab_node));

	return SUCCESS;
}

status direct_addr_delete(struct direct_addr_table *table, int primary_key, struct tab_node *elem)
{
	if(primary_key < table->down_range || primary_key > table->up_range ||
			!table->nodes[primary_key - table->down_range])
		return UNSUCCESS;

	memcpy(elem, table->nodes[primary_key - table->down_range], sizeof(struct tab_node));

	free(table->nodes[primary_key - table->down_range]);
	table->nodes[primary_key - table->down_range] = NULL;

	return SUCCESS;
}

status direct_addr_search(struct direct_addr_table *table, int primary_key, struct tab_node *elem)
{
	if(primary_key < table->down_range || primary_key > table->up_range ||
			!table->nodes[primary_key - table->down_range])
		return UNSUCCESS;

	memcpy(elem, table->nodes[primary_key - table->down_range], sizeof(struct tab_node));

	return SUCCESS;
}

int main(int argc, char *argv[])
{
	int primary_key;
	struct tab_node container;
	struct direct_addr_table table;

	int choice;
	const struct func_info {
		const char *discription;
		int get_flg;
		status (*func)(struct direct_addr_table *, int, struct tab_node *);
	} func_table[] = {
		{ "Exit"	, GET_FROM_FUNC	, NULL				 },
		{ "Insert"	, GET_FROM_STDIN, direct_addr_insert },
		{ "Delete"	, GET_FROM_FUNC	, direct_addr_delete },
		{ "Search"	, GET_FROM_FUNC	, direct_addr_search }
	};

	if(UNSUCCESS == direct_addr_init(&table))
		return EXIT_FAILURE;

	do {
		scanf("%d", &choice);

		if(choice <= 0 || choice >= sizeof(func_table) / sizeof(func_table[0]))
			continue;

		scanf("%d", &primary_key);

		if(GET_FROM_STDIN == func_table[choice].get_flg)
			scanf("%d%s", &container.foreign_key, container.discription);

		if(SUCCESS == func_table[choice].func(&table, primary_key, &container))
			printf("%s {[%d] %d %s} success.\n", func_table[choice].discription, primary_key,
					container.foreign_key, container.discription);
		else
			printf("%s {[%d]} unsucess.\n", func_table[choice].discription, primary_key);

	}while(choice);

	direct_addr_exit(&table);

	return EXIT_SUCCESS;
}
