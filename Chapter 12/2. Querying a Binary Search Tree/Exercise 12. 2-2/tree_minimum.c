#include <stdio.h>
#include <stdlib.h>


struct bt_node {
	int data;
	struct bt_node *lchild, *rchild, *parent;
};


struct bt_node *bst_minimum(struct bt_node *root);


#if 0
struct bt_node *bst_minimum(struct bt_node *root)
{
	if(!root)
		return NULL;

	while(root->lchild)
		root = root->lchild;

	return root;
}
#else
struct bt_node *bst_minimum(struct bt_node *root)
{
	if(!root || !root->lchild)
		return root;

	return bst_minimum(root->lchild);
}
#endif

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
