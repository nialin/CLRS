#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>


void exchange(int *a, int *b);

int random_partition(int *arr, int low, int high);
void quick_sort(int *arr, int low, int high);

void list_show(int *arr, int cnts);


void exchange(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int random_partition(int *arr, int low, int high)
{
	int i, j, pivot;

	srand(time(NULL));
	exchange(&arr[rand() % (high - low + 1) + low], &arr[high]);

	pivot = arr[high];

	for(i = j = low; j < high; ++j)
		if(arr[j] < pivot)
			exchange(&arr[i++], &arr[j]);

	exchange(&arr[i], &arr[high]);

	return i;
}

void quick_sort(int *arr, int low, int high)
{
	int mid;

	if(low < high) {
		mid = random_partition(arr, low, high);

		quick_sort(arr, low, mid - 1);
		quick_sort(arr, mid + 1, high);
	}
}

void list_show(int *arr, int len)
{
	int i;

	for(i = 0; i < len; ++i)
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

	return EXIT_SUCCESS;
}
