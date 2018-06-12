#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>


void exchange(int *a, int *b);

int partition(int *arr, int low, int high);
void quick_sort(int *arr, int low, int high);

void list_show(int *arr, int len);


void exchange(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int *arr, int low, int high)
{
	int i, j, indices[3];
	int pivot;

	srand(time(NULL));

	for(i = 0; i < 3; ++i)
		indices[i] = rand() % (high - low + 1) + low;

	if(((arr[indices[0]] - arr[indices[1]]) ^ (arr[indices[0]] - arr[indices[2]])) < 0)
		exchange(&arr[indices[0]], &arr[high]);
	else if(((arr[indices[1]] - arr[indices[0]]) ^ (arr[indices[1]] - arr[indices[2]])) < 0)
		exchange(&arr[indices[1]], &arr[high]);
	else
		exchange(&arr[indices[2]], &arr[high]);

	pivot = arr[high];

	for(i = j = low; i < high; ++i)
		if(arr[i] < pivot)
			exchange(&arr[j++], &arr[i]);

	exchange(&arr[j], &arr[high]);

	return j;
}

void quick_sort(int *arr, int low, int high)
{
	int mid;

	if(low < high) {
		mid = partition(arr, low, high);

		quick_sort(arr, low, mid - 1);
		quick_sort(arr, mid + 1, high);
	}
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
	int *arr, i, cnt;

	scanf("%d", &cnt);

	if(!(arr = malloc(cnt * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnt; ++i)
		scanf("%d", &arr[i]);

	quick_sort(arr, 0, cnt - 1);
	list_show(arr, cnt);

	free(arr);

	return EXIT_SUCCESS;
}
