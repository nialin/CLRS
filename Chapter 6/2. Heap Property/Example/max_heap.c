#include <stdio.h>
#include <stdlib.h>

#define HEAP_MAX_SIZE	(1024)


struct max_heap{
	int data[HEAP_MAX_SIZE + 1];
	int size;
};


void exchange(int *a, int *b);
void max_heapify(struct max_heap *heap, int i);


void exchange(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* We assume that both LEFT(i) and RIGHT(i) are MAX-HEAP. */
void max_heapify(struct max_heap *heap, int i)
{
	int left = i * 2, right = i * 2 + 1, largest = i;

	if(left <= heap->size && heap->data[left] > heap->data[i])
		largest = left;

	if(right <= heap->size && heap->data[right] > heap->data[largest])
		largest = right;

	if(largest != i) {
		exchange(&heap->data[largest], &heap->data[i]);
		max_heapify(heap, largest);
	}
}

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
