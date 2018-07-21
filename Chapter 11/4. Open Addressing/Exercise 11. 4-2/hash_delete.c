#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LARGE_PRIME			(49999)

#define HASH_TABLE_SIZE		(4096)

#define HASH_SLOT_USED		(1)
#define HASH_SLOT_FREE		(0)
#define HASH_SLOT_DELETE	(-1)

#define UNSUCCESS	(0)
#define SUCCESS		(1)

typedef int status;

struct tab_node {
	int key, flg;
};

struct hash_table {
	struct tab_node slots[HASH_TABLE_SIZE];
};


int hash_func_division(int key, int i);

void hash_table_init(struct hash_table *table);
void hash_table_destroy(struct hash_table *table);

status hash_table_insert(struct hash_table *table, int key);
status hash_table_delete(struct hash_table *table, int key);
status hash_table_search(struct hash_table *table, int key);


int hash_func_division(int key, int i)
{
	return (key + i) % LARGE_PRIME;
}

void hash_table_init(struct hash_table *table)
{
	memset(table->slots, 0, sizeof(table->slots));
}

void hash_table_destroy(struct hash_table *table)
{

}

status hash_table_insert(struct hash_table *table, int key)
{
	int i = 0, pos;

	while(HASH_SLOT_USED == table->slots[pos = hash_func_division(key, ++i) % HASH_TABLE_SIZE].flg && i < 1024)
		;

	if(i >= 1024)
		return UNSUCCESS;

	table->slots[pos].key = key;
	table->slots[pos].flg = HASH_SLOT_USED;

	return SUCCESS;
}

status hash_table_delete(struct hash_table *table, int key)
{
	int i = 0, pos;

	while(HASH_SLOT_DELETE == table->slots[pos = hash_func_division(key, ++i) % HASH_TABLE_SIZE].flg ||
			(HASH_SLOT_USED == table->slots[pos].flg && table->slots[pos].key != key))
		;

	if(HASH_SLOT_FREE == table->slots[pos].flg)
		return UNSUCCESS;

	table->slots[pos].flg = HASH_SLOT_DELETE;

	return SUCCESS;
}

status hash_table_search(struct hash_table *table, int key)
{
	int i = 0, pos;

	while(HASH_SLOT_DELETE == table->slots[pos = hash_func_division(key, ++i) % HASH_TABLE_SIZE].flg ||
			(HASH_SLOT_USED == table->slots[pos].flg && table->slots[pos].key != key))
		;

	if(HASH_SLOT_FREE == table->slots[pos].flg)
		return UNSUCCESS;

	return SUCCESS;
}

int main(int argc, char *argv[])
{
	int key;
	struct hash_table table;

	int choice;
	struct func_info {
		char *discription;
		status (*func)(struct hash_table *, int);
	} func_table[] = {
		{ "Exit"	, NULL				},
		{ "Insert"	, hash_table_insert	},
		{ "Delete"	, hash_table_delete	},
		{ "Search"	, hash_table_search	}
	};

	hash_table_init(&table);

	do {
		scanf("%d", &choice);

		if(choice <= 0 || choice >= sizeof(func_table) / sizeof(func_table[0]))
			continue;

		scanf("%d", &key);

		printf("%s [%d] %ssuccess.\n", func_table[choice].discription, key,
				SUCCESS == func_table[choice].func(&table, key) ? "" : "un");
	}while(choice);

	hash_table_destroy(&table);

	return EXIT_SUCCESS;
}
