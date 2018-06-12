#include <stdio.h>
#include <stdlib.h>

#define HEAP_MAX_SIZE (1024)


struct max_heap {
	int data[HEAP_MAX_SIZE + 1];
	int size;
};


void max_heap_creat(struct max_heap *heap);
void max_heapify(struct max_heap *heap, int i);


void max_heap_creat(struct max_heap *heap)
{
	int i;

	scanf("%d", &heap->size);

	for(i = 1; i <= heap->size; ++i)
		scanf("%d", &heap->data[i]);

	for(i = heap->size / 2; i > 0; --i)
		max_heapify(heap, i);
}

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

void max_heap_show(struct max_heap *heap)
{
	int i;

	for(i = 1; i <= heap->size; ++i)
		printf("%d ", heap->data[i]);

	printf("\n");
}

int main(int argc, char *argv[])
{
	struct max_heap heap;

	max_heap_creat(&heap);
	max_heap_show(&heap);

	return EXIT_SUCCESS;
}
