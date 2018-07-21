#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define EXIST		(1)
#define NOT_EXIST	(0)

#define SUCCESS		(0)
#define UNSUCCESS	(1)

/* Assume the max length of words is 4. */
#define STR_MAX_SIZE	(4)
#define DICT_MAX_SIZE	(1024 * 1024)


typedef int status;

struct stack {
	int *data;
	int top, length;
};

struct dict {
	int pos[DICT_MAX_SIZE];
	struct stack stack;
};


int decode(const char *word);

status dict_init(struct dict *dict, int real_size);
status dict_destroy(struct dict *dict);

status dict_insert(struct dict *dict, const char *word);
status dict_delete(struct dict *dict, const char *word);
status dict_search(struct dict *dict, const char *word);


int decode(const char *word)
{
	int i, rslt;

	for(i = 0, rslt = 0; i < STR_MAX_SIZE; ++i) {
		rslt <<= 5;
		rslt += word[i] - 'a';
	}

	return word[i] ? -1 : rslt;
}

status dict_init(struct dict *dict, int real_size)
{
	if(!(dict->stack.data = malloc(real_size * sizeof(int))))
		return UNSUCCESS;

	dict->stack.top = 0;
	dict->stack.length = real_size;

	return SUCCESS;
}

status dict_destroy(struct dict *dict)
{
	if(!dict->stack.data)
		return UNSUCCESS;

	free(dict->stack.data);
	dict->stack.data = NULL;

	dict->stack.top = 0;

	return SUCCESS;
}

status dict_insert(struct dict *dict, const char *word)
{
	int index;

	if(-1 == (index = decode(word)))
		return UNSUCCESS;

	if(dict->pos[index] < dict->stack.top &&
			dict->stack.data[dict->pos[index]] == index)
		return UNSUCCESS;

	dict->stack.data[dict->stack.top] = index;
	dict->pos[index] = dict->stack.top++;

	return SUCCESS;
}

status dict_delete(struct dict *dict, const char *word)
{
	int index;

	if(-1 == (index = decode(word)))
		return UNSUCCESS;

	if(dict->pos[index] >= dict->stack.top ||
			dict->stack.data[dict->pos[index]] != index)
		return UNSUCCESS;

	dict->pos[dict->stack.data[--dict->stack.top]] = dict->pos[index];
	dict->stack.data[dict->pos[index]] = dict->stack.data[dict->stack.top];

	return SUCCESS;
}

status dict_search(struct dict *dict, const char *word)
{
	int index;

	if(-1 == (index = decode(word)))
		return UNSUCCESS;

	if(dict->pos[index] >= dict->stack.top ||
			dict->stack.data[dict->pos[index]] != index)
		return UNSUCCESS;

	return SUCCESS;
}

int main(int argc, char *argv[])
{
	int real_size;
	/*
	 * According to the discription of Practice 11.4, the huge array is uninitialized.
	 * Auto variable is also uninitialized.
	 */
	struct dict dict;
	char word[STR_MAX_SIZE + 1] = {0};

	int choice;
	struct func_info {
		char *discription;
		status (*func)(struct dict *, const char *);
	} func_table[] = {
		{ "Exit"	, NULL 			},
		{ "Insert"	, dict_insert	},
		{ "Delete"	, dict_delete	},
		{ "Search"	, dict_search	}
	};

	scanf("%d", &real_size);

	if(UNSUCCESS == dict_init(&dict, real_size))
		return EXIT_FAILURE;

	do {
		scanf("%d", &choice);

		if(choice <= 0 || choice >= sizeof(func_table) / sizeof(func_table[0]))
			continue;

		scanf("%s", word);

		printf("%s %s %ssuccess.\n", func_table[choice].discription, word,
				SUCCESS == func_table[choice].func(&dict, word) ? "" : "un");
	}while(choice);

	dict_destroy(&dict);

	return EXIT_SUCCESS;
}
