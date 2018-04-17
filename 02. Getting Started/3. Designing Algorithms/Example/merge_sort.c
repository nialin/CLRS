#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>


void merge(int *arr, int low, int mid, int high);
void merge_sort(int *arr, int low, int high);
void list_show(int *arr, int cnts);


void merge(int *arr, int low, int mid, int high)
{
	int i, *tmp_1, *tmp_2, cnts_1, cnts_2, index_1, index_2;

	cnts_1 = mid - low + 1;
	cnts_2 = high - mid;

	if(!(tmp_1 = malloc((cnts_1 + 1) * sizeof(int))))
		exit(ENOMEM);

	if(!(tmp_2 = malloc((cnts_2 + 1) * sizeof(int))))
		exit(ENOMEM);

	memcpy(tmp_1, &arr[low], cnts_1 * sizeof(int));
	memcpy(tmp_2, &arr[mid + 1], cnts_2 * sizeof(int));

	tmp_1[cnts_1] = INT_MAX;
	tmp_2[cnts_2] = INT_MAX;

	for(i = low, index_1 = 0, index_2 = 0; i <= high; ++i)
		arr[i] = tmp_1[index_1] < tmp_2[index_2] ? tmp_1[index_1++] : tmp_2[index_2++];
	
	free(tmp_1);
	free(tmp_2);
}

void merge_sort(int *arr, int low, int high)
{
	int mid;

	if(low < high) {
		mid = (low + high) / 2;

		merge_sort(arr, low, mid);
		merge_sort(arr, mid + 1, high);

		merge(arr, low, mid, high);
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

	merge_sort(arr, 0, cnts - 1);
	
	list_show(arr, cnts);

	free(arr);

	return EXIT_SUCCESS;
}
