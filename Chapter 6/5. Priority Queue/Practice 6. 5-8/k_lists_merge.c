#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define HEAP_MAX_SIZE	(1024)
#define LIST_MAX_SIZE	(100)


struct link_node {
	int data;
	struct link_node *next;
};

struct max_heap {
	struct link_node *data[HEAP_MAX_SIZE + 1];
	int size;
};


int compare(const void *a, const void *b);

void max_heap_creat(struct max_heap *heap);
void max_heapify(struct max_heap *heap, int i);

struct link_node *sorted_linklist_creat(void);
struct link_node *sorted_list_merge(struct max_heap *heap);

void list_show(struct link_node *head);
void list_destroy(struct link_node **head);


int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

void max_heap_creat(struct max_heap *heap)
{
	int i;

	scanf("%d", &heap->size);

	for(i = 1; i <= heap->size; ++i)
		heap->data[i] = sorted_linklist_creat();

	for(i = heap->size / 2; i > 0; --i)
		max_heapify(heap, i);
}

void max_heapify(struct max_heap *heap, int i)
{
	struct link_node *tmp = heap->data[i];

	for(i *= 2; i <= heap->size; i *= 2) {
		if(i < heap->size && heap->data[i]->data < heap->data[i + 1]->data)
			++i;

		if(heap->data[i]->data < tmp->data)
			break;

		heap->data[i / 2] = heap->data[i];
	}
	heap->data[i / 2] = tmp;
}

struct link_node *sorted_linklist_creat(void)
{
	struct link_node *head = NULL, *new;
	int i, cnts, tmp[LIST_MAX_SIZE];

	scanf("%d", &cnts);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &tmp[i]);

	qsort(tmp, cnts, sizeof(int), compare);

	for(i = 0; i < cnts; ++i) {
		if(!(new = malloc(sizeof(struct link_node))))
			exit(ENOMEM);

		new->data = tmp[i];

		new->next = head;
		head = new;
	}

	return head;
}

struct link_node *sorted_list_merge(struct max_heap *heap)
{
	struct link_node *head = NULL, *new;

	while(heap->size) {
		new = heap->data[1];
		heap->data[1] = heap->data[1]->next;

		new->next = head;
		head = new;

		if(!heap->data[1])
			heap->data[1] = heap->data[heap->size--];

		max_heapify(heap, 1);
	}

	return head;
}

void list_show(struct link_node *head)
{
	for( ; head; head = head->next)
		printf("%d ", head->data);

	printf("\n");
}

void list_destroy(struct link_node **head)
{
	if(*head) {
		list_destroy(&(*head)->next);

		free(*head);
		*head = NULL;
	}
}

int main(int argc, char *argv[])
{
	struct max_heap heap;
	struct link_node *head;

	max_heap_creat(&heap);
	head = sorted_list_merge(&heap);
	list_show(head);

	list_destroy(&head);

	return EXIT_SUCCESS;
}
