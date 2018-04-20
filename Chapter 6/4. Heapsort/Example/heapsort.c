#include <stdio.h>
#include <stdlib.h>

#define HEAP_MAX_SIZE	(1024)


struct max_heap{
	int data[HEAP_MAX_SIZE + 1];
	int size;
};


/* For output. */
int cnts;

void exchange(int *a, int *b);

void max_heap_creat(struct max_heap *heap);
void max_heapify(struct max_heap *heap, int i);

void heap_sort(struct max_heap *heap);


void exchange(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void max_heap_creat(struct max_heap *heap)
{
	int i;

	scanf("%d", &heap->size);
	cnts = heap->size;

	for(i = 1; i <= heap->size; ++i)
		scanf("%d", &heap->data[i]);

	for(i = heap->size / 2; i > 0; --i)
		max_heapify(heap, i);
}

#if 0
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

void heap_sort(struct max_heap *heap)
{
	int i;

	max_heap_creat(heap);

	for(i = heap->size; i > 1; --i) {
		exchange(&heap->data[1], &heap->data[i]);
		--heap->size;
		max_heapify(heap, 1);
	}
}

int main(int argc, char *argv[])
{
	int i;
	struct max_heap heap;

	heap_sort(&heap);

	for(i = 1; i <= cnts; ++i)
		printf("%d ", heap.data[i]);

	printf("\n");

	return EXIT_SUCCESS;
}
