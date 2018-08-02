#include <stdio.h>
#include <stdlib.h>


struct bt_node {
	int data;
	struct bt_node *lchild, *rchild, *parent;
};


struct bt_node *bst_maximum(struct bt_node *root);


#if 0
struct bt_node *bst_maximum(struct bt_node *root)
{
	if(!root)
		return NULL;

	while(root->rchild)
		root = root->rchild;

	return root;
}
#else
struct bt_node *bst_maximum(struct bt_node *root)
{
	if(!root || !root->rchild)
		return root;

	return bst_maximum(root->rchild);
}
#endif

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
