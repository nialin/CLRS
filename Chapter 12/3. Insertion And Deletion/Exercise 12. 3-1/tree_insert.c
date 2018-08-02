#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>

#define UNSUCCESS	(0)
#define SUCCESS		(1)

#define DEBUG	(1)

typedef int status;

struct bt_node {
	int data;
	struct bt_node *lchild, *rchild, *parent;
};


status bst_insert(struct bt_node **root, struct bt_node *parent, int data);


status bst_insert(struct bt_node **root, struct bt_node *parent, int data)
{
	if(!(*root)) {
		if(!(*root = malloc(sizeof(struct bt_node))))
			return UNSUCCESS;

		(*root)->data = data;
		(*root)->lchild = (*root)->rchild = NULL;
		(*root)->parent = parent;

		return SUCCESS;
	}

	if(data == (*root)->data)
		return UNSUCCESS;

	if(data < (*root)->data)
		return bst_insert(&(*root)->lchild, *root, data);
	else
		return bst_insert(&(*root)->rchild, *root, data);
}

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
