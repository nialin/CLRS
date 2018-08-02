#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define RADIX_TREE_ENTRY_MASK	(1)
#define RADIX_TREE_LCHILD_MASK	(2)
#define RADIX_TREE_RCHILD_MASK	(4)

#define UNSUCCESS	(0)
#define SUCCESS		(1)


typedef int status;

/*
 * @mask:
 *	bit[0]					bit[1]						bit[2]						bit[3-7]
 *		0 - internal nod		0 - hasn't left child		0 - hasn't right child		unused/reserved
 *		1 - entry node			1 - has left child			1 - has right child
 */
struct radix_tree_node {
	unsigned char mask;
	struct radix_tree_node *lchild, *rchild, *parent;
};


void radix_tree_init(struct radix_tree_node **root);
void radix_tree_destroy(struct radix_tree_node **root);

status radix_tree_insert(struct radix_tree_node *root, const char *str);
status radix_tree_delete(struct radix_tree_node *root, const char *str);
status radix_tree_search(struct radix_tree_node *root, const char *str);


void radix_tree_init(struct radix_tree_node **root)
{
	if(!(*root = malloc(sizeof(struct radix_tree_node))))
		exit(ENOMEM);

	(*root)->mask = 0;
	(*root)->lchild = (*root)->rchild = (*root)->parent = NULL;
}

void radix_tree_destroy(struct radix_tree_node **root)
{
	if(*root) {
		radix_tree_destroy(&(*root)->lchild);
		radix_tree_destroy(&(*root)->rchild);

		free(*root);
		*root = NULL;
	}
}

status radix_tree_insert(struct radix_tree_node *root, const char *str)
{
	while(*str) {
		if('0' == *str++) {
			if(!(root->mask & RADIX_TREE_LCHILD_MASK)) {
				root->mask |= RADIX_TREE_LCHILD_MASK;

				if(!(root->lchild = malloc(sizeof(struct radix_tree_node))))
					return UNSUCCESS;

				root->lchild->lchild = root->lchild->rchild = NULL;
				root->lchild->parent = root;
			}

			root = root->lchild;
		}
		else {
			if(!(root->mask & RADIX_TREE_RCHILD_MASK)) {
				root->mask |= RADIX_TREE_RCHILD_MASK;

				if(!(root->rchild = malloc(sizeof(struct radix_tree_node))))
					return UNSUCCESS;

				root->rchild->lchild = root->rchild->rchild = NULL;
				root->rchild->parent = root;
			}

			root = root->rchild;
		}
	}

	root->mask |= RADIX_TREE_ENTRY_MASK;

	return SUCCESS;
}

status radix_tree_delete(struct radix_tree_node *root, const char *str)
{
	while(*str && root)
		root = '0' == *str++ ? root->lchild : root->rchild;

	if(!root || !(root->mask & RADIX_TREE_ENTRY_MASK))
		return UNSUCCESS;

	for(root->mask &= ~RADIX_TREE_ENTRY_MASK; 0 == root->mask; ) {
		root = root->parent;

		if('0' == *--str) {
			free(root->lchild);
			root->lchild = NULL;
			root->mask &= ~RADIX_TREE_LCHILD_MASK;
		}
		else {
			free(root->rchild);
			root->rchild = NULL;
			root->mask &= ~RADIX_TREE_RCHILD_MASK;
		}
	}

	return SUCCESS;
}

status radix_tree_search(struct radix_tree_node *root, const char *str)
{
	while(*str && root)
		root = '0' == *str++ ? root->lchild : root->rchild;

	return root && root->mask & RADIX_TREE_ENTRY_MASK;
}

int main(int argc, char *argv[])
{
	char str[10] = {0};
	struct radix_tree_node *root = NULL;

	int choice;
	struct func_info {
		char *discription;
		status (*func)(struct radix_tree_node *, const char *);
	} func_table[] = {
		{ "Exit"	, NULL				},
		{ "Insert"	, radix_tree_insert	},
		{ "Delete"	, radix_tree_delete	},
		{ "Search"	, radix_tree_search	}
	};

	radix_tree_init(&root);

	do {
		scanf("%d", &choice);

		if(choice <= 0 || choice >= sizeof(func_table) / sizeof(func_table[0]))
			continue;

		scanf("%s", str);

		printf("%s [%s] %ssuccess.\n", func_table[choice].discription, str,
				SUCCESS == func_table[choice].func(root, str) ? "" : "un");

	}while(choice);

	radix_tree_destroy(&root);

	return EXIT_SUCCESS;
}
