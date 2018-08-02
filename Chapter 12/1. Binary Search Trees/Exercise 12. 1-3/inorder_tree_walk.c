#include <stdio.h>
#include <stdlib.h>


struct bt_node {
	int data;
	struct bt_node *lchild, *rchild, *parent;
};


void inorder_tree_walk(struct bt_node *root);


void inorder_tree_walk(struct bt_node *root)
{
	int top = 0;
	struct bt_node *stack[1024] = {NULL};

	while(root || top) {
		if(root) {
			stack[top++] = root;
			root = root->lchild;
		}
		else {
			root = stack[--top];
			printf("%d ", root->data);
			root = root->rchild;
		}
	}
}

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
