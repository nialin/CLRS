#include <stdio.h>
#include <stdlib.h>


struct bt_node {
	int data;
	struct bt_node *lchild, *rchild, *parent;
};


void inorder_tree_walk(struct bt_node *root);


void inorder_tree_walk(struct bt_node *root)
{
	if(!root)
		return ;

	inorder_tree_walk(root->lchild);
	printf("%d ", root->data);
	inorder_tree_walk(root->rchild);
}

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
