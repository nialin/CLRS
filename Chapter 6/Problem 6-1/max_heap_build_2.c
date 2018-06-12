#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define HEAP_MAX_SIZE (1024)


struct max_heap {
	int data[HEAP_MAX_SIZE + 1];
	int size;
};


void max_heap_creat(struct max_heap *heap);
void max_heapify(struct max_heap *heap, int i);

void max_heap_insert(struct max_heap *heap ,int key);
void max_heap_increase_key(struct max_heap *heap, int i, int key);

void max_heap_show(struct max_heap *heap);


void max_heap_creat(struct max_heap *heap)
{
	int i, cnt, data;

	scanf("%d", &cnt);

	for(i = 1; i <= cnt; ++i) {
		scanf("%d", &data);
		max_heap_insert(heap, data);
	}
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

void max_heap_insert(struct max_heap *heap ,int key)
{
	if(heap->size >= HEAP_MAX_SIZE)
		return ;

	heap->data[++heap->size] = INT_MIN;
	
	max_heap_increase_key(heap, heap->size, key);
}

void max_heap_increase_key(struct max_heap *heap, int i, int key)
{
	if(i > heap->size || key < heap->data[i])
		return ;

	for( ; i > 1 && key > heap->data[i / 2]; i /= 2)
		heap->data[i] = heap->data[i / 2];

	heap->data[i] = key;
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
