#include <stdio.h>
#include <stdlib.h>

#define HEAP_MAX_SIZE   (1024)


struct max_heap {
    int data[HEAP_MAX_SIZE + 1];
    int size;
};


void max_heapify(struct max_heap *heap, int i);
void max_heap_delete(struct max_heap *heap, int i);


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

void max_heap_delete(struct max_heap *heap, int i)
{
    int tmp;

    if(i > heap->size)
        return ;

    heap->data[i] = heap->data[heap->size--];

    if(heap->data[i] < heap->data[i / 2])
        max_heapify(heap, i);
    else {
        tmp = heap->data[i];

        for( ; i > 1 && tmp > heap->data[i / 2]; i /= 2)
            heap->data[i] = heap->data[i / 2];

        heap->data[i] = tmp;
    }
}

int main(int argc, char *argv[])
{
    return EXIT_SUCCESS;
}
