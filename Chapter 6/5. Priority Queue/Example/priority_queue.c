#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define QUEUE_MAX_SIZE	(1024)


struct priority_queue {
	int data[QUEUE_MAX_SIZE + 1];
	int size;
};


void priority_queueify(struct priority_queue *queue, int i);

int priority_queue_maximum(struct priority_queue *queue);
int priority_queue_extract_max(struct priority_queue *queue);

void priority_queue_insert(struct priority_queue *queue, int key);
void priority_queue_increase(struct priority_queue *queue, int i, int key);


void priority_queueify(struct priority_queue *queue, int i)
{
	int tmp = queue->data[i];

	for(i *= 2; i <= queue->size; i *= 2) {
		if(i < queue->size && queue->data[i] < queue->data[i + 1])
			++i;

		if(queue->data[i] < tmp)
			break;

		queue->data[i / 2] = queue->data[i];
	}

	queue->data[i / 2] = tmp;
}

int priority_queue_maximum(struct priority_queue *queue)
{
	if(queue->size < 1)
		return -1;

	return queue->data[1];
}

int priority_queue_extract_max(struct priority_queue *queue)
{
	int max;

	if(queue->size < 1)
		return -1;

	max = queue->data[1];

	queue->data[1] = queue->data[queue->size];
	--queue->size;

	priority_queueify(queue, 1);

	return max;
}

void priority_queue_insert(struct priority_queue *queue, int key)
{
	if(queue->size >= QUEUE_MAX_SIZE)
		return ;

	queue->data[++queue->size] = INT_MIN;

	priority_queue_increase(queue, queue->size, key);
}

void priority_queue_increase(struct priority_queue *queue, int i, int key)
{
	if(i > queue->size || key < queue->data[i])
		return ;

	for( ; i > 1 && key > queue->data[i / 2]; i /= 2)
		queue->data[i] = queue->data[i / 2];

	queue->data[i] = key;
}

int main(int argc, char *argv[])
{
	return EXIT_SUCCESS;
}
