#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


struct bucket {
	int data;
	struct bucket *next;
};


int main(int argc, char *argv[])
{
	int i, cnt, data, index;
	struct bucket list[10] = {{0}}, *ptr, *new;

	scanf("%d", &cnt);

	/* Bucket Sort */
	for(i = 0; i < cnt; ++i) {
		scanf("%d", &data);

		index = data / 10;

		for(ptr = &list[index]; ptr->next && ptr->next->data < data; ptr = ptr->next)
			;

		if(!(new = malloc(sizeof(struct bucket))))
			exit(ENOMEM);
		new->data = data;
		new->next = ptr->next;

		ptr->next = new;
	}

	for(i = 0; i < 10; ++i) {
		for(ptr = list[i].next; ptr; ptr = ptr->next)
			printf("%d ", ptr->data);
	}

	printf("\n");

	for(i = 0; i < 10; ++i) {
		for(ptr = list[i].next; ptr; ptr = list[i].next) {
			list[i].next = ptr->next;
			free(ptr);
		}
	}

	return EXIT_SUCCESS;
}
