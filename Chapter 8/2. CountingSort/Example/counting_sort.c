#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NUM_RANGE	(1024)


void list_show(int *arr, int cnt);
void counting_sort(int *arr, int cnt);


void counting_sort(int *arr, int cnt)
{
	int i, *tmp, cnts[NUM_RANGE] = {0};

	if(!(tmp = malloc(cnt * sizeof(int))))
		exit(ENOMEM);

	memcpy(tmp, arr, cnt * sizeof(int));

	for(i = 0; i < cnt; ++i)
		++cnts[tmp[i]];

	for(i = 1; i < NUM_RANGE; ++i)
		cnts[i] += cnts[i - 1];

	/* The following code makes COUNTING-SORT stable. */
	for(i = cnt - 1; i >= 0; --i)
		arr[--cnts[tmp[i]]] = tmp[i];
}

void list_show(int *arr, int cnt)
{
	int i;

	for(i = 0; i < cnt; ++i)
		printf("%d ", arr[i]);

	printf("\n");
}

int main(int argc, char *argv[])
{
	int i, cnt, *arr;

	scanf("%d", &cnt);

	if(!(arr = malloc(cnt * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnt; ++i)
		scanf("%d", &arr[i]);

	counting_sort(arr, cnt);

	list_show(arr, cnt);

	free(arr);

	return EXIT_SUCCESS;
}
