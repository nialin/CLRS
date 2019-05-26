#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define RBTREE_RED		(0)
#define RBTREE_BLACK	(1)

#define TRUE		(1 == 1)
#define FALSE		(!TRUE)


struct rb_node {
	int data;
	int color;
	struct rb_node *lchild, *rchild, *parent;
};

struct rb_root {
	struct rb_node *node;
};


void left_rotate(struct rb_root *root, struct rb_node *node);
void right_rotate(struct rb_root *root, struct rb_node *node);


void left_rotate(struct rb_root *root, struct rb_node *node)
{
	struct rb_node *right = node->rchild, *parent = node->parent;

	if(node->rchild = right->lchild)
		right->lchild->parent = node;

	right->lchild = node;

	if(parent){
		if(node == parent->lchild)
			parent->lchild = right;
		else
			parent->rchild = right;
	}
	else
		root->node = right;

	node->parent = right;
}

void right_rotate(struct rb_root *root, struct rb_node *node)
{
	struct rb_node *left = node->lchild, *parent = node->parent;

	if(node->lchild = left->rchild)
		left->rchild->parent = node;

	left->rchild = node;

	if(parent) {
		if(node == parent->lchild)
			parent->lchild = left;
		else
			parent->rchild = left;
	}
	else
		root->node = left;

	node->parent = left;
}

void rbtree_insert_fixup(struct rb_root *root, struct rb_node *node)
{
	struct rb_node *gparent, *uncle;

	while(RBTREE_RED == node->parent->color) {
		gparent = node->parent->parent;

		if(node->parent == gparent->lchild) {
			uncle = node->rchild;

			if(uncle && RBTREE_RED == uncle->color) {
				/*
				 *	Case 1 - node's uncle is red.
				 *
				 *		G			g
				 *	   / \		   / \
				 *	  p	  u	 ->	  P	  U
				 *	 /			 /
				 *  n			n
				 *
				 */
				gparent->color = RBTREE_RED;
				uncle->color = RBTREE_BLACK;
				node->parent->color = RBTREE_BLACK;
	
				node = gparent;
			}
			else {
				if(node == node->parent->rchild) {
					/*
					 *	Case 2 - node, parent and grandparent is zigzag.
					 *
					 *		G			 G
					 *	   / \		    / \
					 *	  p	  U	  ->   n   U
					 *	   \		  /
					 *  	n		 p
					 *
					 */
					left_rotate(root, node);
					node = node->lchild;
				}

				/*
				 *	Case 3 - node, parent and grandparent is in a line.
				 *
				 *		G		     P
				 *	   / \		  	/ \
				 *	  p	  U	  ->   n   g
				 *	 /				    \
				 *  n					 U
				 *
				 */
				gparent->color = RBTREE_RED;
				node->parent->color = RBTREE_BLACK;
				right_rotate(root, node->parent);
			}
		}
		else {
			uncle = node->lchild;

			if(uncle && RBTREE_RED == uncle->color) {
				gparent->color = RBTREE_RED;
				uncle->color = RBTREE_BLACK;
				node->parent->color = RBTREE_BLACK;
	
				node = gparent;
			}
			else {
				if(node == node->parent->lchild) {
					right_rotate(root, node);
					node = node->rchild;
				}

				gparent->color = RBTREE_RED;
				node->parent->color = RBTREE_BLACK;
				left_rotate(root, node->parent);
			}
		}
	}
}

int rbtree_insert(struct rb_root *root, int data)
{
	struct rb_node **t;

	while(*t) {
		if(data == (*t)->data)
			return FALSE;

		if(data < (*t)->data)
			t = &(*t)->lchild;
		else
			t = &(*t)->rchild;
	}

	if(!(*t = malloc(sizeof(struct rb_node))))
		exit(ENOMEM);

	(*t)->data = data;
	(*t)->lchild = (*t)->rchild = NULL;
	(*t)->color = RBTREE_RED;

	rbtree_insert_fixup(root, *t);

	return TRUE;
}

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
