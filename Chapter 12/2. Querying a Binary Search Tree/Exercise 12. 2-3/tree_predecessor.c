#include <stdio.h>
#include <stdlib.h>


struct bt_node {
	int data;
	struct bt_node *lchild, *rchild, *parent;
};


struct bt_node *bst_maximum(struct bt_node *root);
struct bt_node *bst_predecessor(struct bt_node *root);


struct bt_node *bst_maximum(struct bt_node *root)
{
	if(!root)
		return NULL;

	while(root->rchild)
		root = root->rchild;

	return root;
}

struct bt_node *bst_predecessor(struct bt_node *root)
{
	struct bt_node *pre;

	if(root->lchild)
		return bst_maximum(root->lchild);

	for(pre = root->parent; pre && root == pre->lchild; root = pre, pre = pre->parent)
		;

	return pre;
}

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
