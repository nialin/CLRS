#include <stdio.h>
#include <stdlib.h>


struct bt_node {
	int data;
	struct bt_node *lchild, *rchild, *parent;
};


void preorder_tree_walk(struct bt_node *root);
void postorder_tree_walk(struct bt_node *root);


void preorder_tree_walk(struct bt_node *root)
{
	if(!root)
		return ;

	printf("%d ", root->data);
	preorder_tree_walk(root->lchild);
	preorder_tree_walk(root->rchild);
}

void postorder_tree_walk(struct bt_node *root)
{
	if(!root)
		return ;

	postorder_tree_walk(root->lchild);
	postorder_tree_walk(root->rchild);
	printf("%d ", root->data);
}

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
