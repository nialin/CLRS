#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void selection_sort(int *arr, int cnts);
void list_show(int *arr, int cnts);


void selection_sort(int *arr, int cnts)
{
	int i, j, min_pos, tmp;

	for(i = 0; i < cnts - 1; ++i) {
		for(min_pos = i, j = i + 1; j < cnts; ++j) {
			if(arr[j] < arr[min_pos])
				min_pos = j;
		}

		tmp = arr[min_pos];
		arr[min_pos] = arr[i];
		arr[i] = tmp;
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

	selection_sort(arr, cnts);

	list_show(arr, cnts);

	free(arr);

	return EXIT_SUCCESS;
}
