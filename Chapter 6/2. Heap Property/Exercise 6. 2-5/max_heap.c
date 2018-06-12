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

#if 0
/* We assume that both LEFT(i) and RIGHT(i) are MAX-HEAP. */
void max_heapify(struct max_heap *heap, int i)
{
	int largest;

	for(largest = i * 2; largest <= heap->size; largest *= 2) {
		if(largest < heap->size && heap->data[largest] < heap->data[largest + 1])
			++largest;

		if(heap->data[largest] < heap->data[i])
			break;

		exchange(&heap->data[largest], &heap->data[i]);
		i = largest;
	}
}
#else
void max_heapify(struct max_heap *heap, int i)
{
	int tmp = heap->data[i];

	for(i *= 2; i <= heap->size; i *= 2) {
		if(i < heap->size && heap->data[i] < heap->data[i + 1])
			++i;

		if(heap->data[i] < tmp)
			break;

		heap->data[i / 2] = heap->data[i];
	}

	heap->data[i / 2] = tmp;
}
#endif

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
