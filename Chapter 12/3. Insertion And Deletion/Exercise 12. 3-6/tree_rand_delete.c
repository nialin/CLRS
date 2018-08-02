#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define UNSUCCESS	(0)
#define SUCCESS		(1)

#define DEBUG	(1)

typedef int status;

struct bt_node {
	int data;
	struct bt_node *lchild, *rchild, *parent;
};


status bst_insert(struct bt_node **root, int data);
status bst_delete(struct bt_node **root, int data);
status bst_search(struct bt_node **root, int data);

void inorder_tree_walk(struct bt_node *root);

void bst_destroy(struct bt_node **root);


status bst_insert(struct bt_node **root, int data)
{
	struct bt_node *parent = NULL;

	while(*root) {
		if(data == (*root)->data)
			return UNSUCCESS;

		parent = *root;

		if(data < (*root)->data)
			root = &(*root)->lchild;
		else
			root = &(*root)->rchild;
	}

	if(!(*root = malloc(sizeof(struct bt_node))))
		return UNSUCCESS;

	(*root)->data = data;
	(*root)->lchild = (*root)->rchild = NULL;
	(*root)->parent = parent;

	return SUCCESS;
}

status bst_delete(struct bt_node **root, int data)
{
	struct bt_node *del, **adopt;

	srand(time(NULL));

	while(*root) {
		if(data == (*root)->data) {
			if((*root)->lchild && (*root)->rchild) {
				if(rand() & 1) {
					for(del = (*root)->rchild; del->lchild; del = del->lchild)
						;

					(*root)->data = del->data;

					adopt = *root == del->parent ? &del->parent->rchild : &del->parent->lchild;
					*adopt = del->rchild;

					if(del->rchild)
						del->rchild->parent = del->parent;
				}
				else {
					for(del = (*root)->lchild; del->rchild; del = del->rchild)
						;

					(*root)->data = del->data;

					adopt = *root == del->parent ? &del->parent->lchild : &del->parent->rchild;
					*adopt = del->lchild;

					if(del->lchild)
						del->lchild->parent = del->parent;
				}
			}
			else {
				del = *root;
				*root = (*root)->lchild ? (*root)->lchild : (*root)->rchild;

				if(*root)
					(*root)->parent = del->parent;
			}

			free(del);

			return SUCCESS;
		}

		if(data < (*root)->data)
			root = &(*root)->lchild;
		else
			root = &(*root)->rchild;
	}

	return UNSUCCESS;
}

status bst_search(struct bt_node **root, int data)
{
	while(*root) {
		if(data == (*root)->data)
			return SUCCESS;

		if(data < (*root)->data)
			root = &(*root)->lchild;
		else
			root = &(*root)->rchild;
	}

	return UNSUCCESS;
}

void inorder_tree_walk(struct bt_node *root)
{
	if(!root)
		return ;

	inorder_tree_walk(root->lchild);
	printf("%d ", root->data);
	inorder_tree_walk(root->rchild);
}

void bst_destroy(struct bt_node **root)
{
	if(*root) {
		bst_destroy(&(*root)->lchild);
		bst_destroy(&(*root)->rchild);

		free(*root);
		*root = NULL;
	}
}

int main(int argc, char *argv[])
{
	int data;
	struct bt_node *root = NULL;

	int choice;
	struct func_info {
		char *discription;
		status (*func)(struct bt_node **, int);
	} func_table[] = {
		{ "Exit"	, NULL			},
		{ "Insert"	, bst_insert	},
		{ "Delete"	, bst_delete	},
		{ "Search"	, bst_search	}
	};

	do {
		scanf("%d", &choice);

		if(choice <= 0 || choice >= sizeof(func_table) / sizeof(func_table[0]))
			continue;

		scanf("%d", &data);

		printf("%s [%d] %ssuccess.\n", func_table[choice].discription, data,
				SUCCESS == func_table[choice].func(&root, data) ? "" : "un");
#if DEBUG
		inorder_tree_walk(root);
		printf("\n");
#endif
	}while(choice);

	bst_destroy(&root);

	return EXIT_SUCCESS;
}
