#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


struct bt_node {
	int data;
	struct bt_node *lchild, *rchild, *parent;
};


struct bt_node *bst_search(struct bt_node *root, int data);

struct bt_node *bst_minimum(struct bt_node *root);
struct bt_node *bst_maximum(struct bt_node *root);

struct bt_node *bst_predecessor(struct bt_node *root);
struct bt_node *bst_successor(struct bt_node *root);

void inorder_tree_walk(struct bt_node *root);


struct bt_node *bst_search(struct bt_node *root, int data)
{
	while(root) {
		if(data == root->data)
			return root;

		if(data < root->data)
			root = root->lchild;
		else
			root = root->rchild;
	}

	return NULL;
}

struct bt_node *bst_minimum(struct bt_node *root)
{
	if(!root)
		return NULL;

	while(root->lchild)
		root = root->lchild;

	return root;
}

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

struct bt_node *bst_successor(struct bt_node *root)
{
	struct bt_node *su;

	if(root->rchild)
		return bst_minimum(root->rchild);

	for(su = root->parent; su && root == su->rchild; root = su, su = su->parent)
		;

	return su;
}

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
