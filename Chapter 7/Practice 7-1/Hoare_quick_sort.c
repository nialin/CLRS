#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void exchange(int *a, int *b);

int hoare_partition(int *arr, int low, int high);
void quick_sort(int *arr, int low, int high);

void list_show(int *arr, int cnts);


void exchange(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int hoare_partition(int *arr, int low, int high)
{
	int pivot = arr[low];

	while(1) {
		while(arr[low] < pivot)
			++low;

		while(arr[high] > pivot)
			--high;

		if(low < high)
			exchange(&arr[low], &arr[high]);
		else
			return high;
	}
}

void quick_sort(int *arr, int low, int high)
{
	int mid;

	if(low < high) {
		mid = hoare_partition(arr, low, high);

		quick_sort(arr, low, mid);
		quick_sort(arr, mid + 1, high);
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

	quick_sort(arr, 0, cnts - 1);
	list_show(arr, cnts);

	free(arr);

	return EXIT_SUCCESS;
}
