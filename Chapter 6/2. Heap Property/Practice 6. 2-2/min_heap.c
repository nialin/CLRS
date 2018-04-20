#include <stdio.h>
#include <stdlib.h>

#define HEAP_MAX_SIZE	(1024)


struct min_heap {
	int data[HEAP_MAX_SIZE + 1];
	int size;
};


void exchange(int *a, int *b);
void min_heapify(struct min_heap *heap, int i);


void exchange(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* We assume that both LEFT(i) and RIGHT(i) are MIN-HEAP */
void min_heapify(struct min_heap *heap, int i)
{
	int left = i * 2, right = i * 2 + 1, smallest = i;

	if(left <= heap->size && heap->data[left] < heap[i])
		smallest = left;

	if(right <= heap->size && heap->data[right] < heap[smallest])
		smallest = right;

	if(smallest != i) {
		exchange(&heap->data[smallest], &heap->data[i]);
		min_heapify(heap, smallest);
	}
}

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
