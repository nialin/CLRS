#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void insertion_sort(int *arr, int cnts);
void list_show(int *arr, int cnts);


void insertion_sort(int *arr, int cnts)
{
	int i, j, key;

	for(j = 1; j < cnts; ++j) {
		for(i = j - 1, key = arr[j]; i >= 0 && arr[i] > key; --i)
			arr[i + 1] = arr[i];

		arr[i + 1] = key;
	}
}

void list_show(int *arr, int cnts)
{
	int i;

	for(i = 0; i < cnts; ++i)
		printf("%d ", arr[i]);

	printf("\n");
}

int main(int argc, char *argv[])
{
	int *arr, i, cnts;

	scanf("%d", &cnts);

	if(!(arr = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &arr[i]);

	insertion_sort(arr, cnts);

	list_show(arr, cnts);

	free(arr);

	return EXIT_SUCCESS;
}
