#include <stdio.h>
#include <stdlib.h>


void insertion_sort(int *arr, int cnt);
void list_print(int *arr, int cnt);


int binary_search(int *arr, int low, int high, int v)
{
	int mid;

	while(low <= high) {
		mid = (low + high) / 2;

		if(arr[mid] <= v)
			low = mid + 1;
		else
			high = mid - 1;
	}

	return low;
}

void insertion_sort(int *arr, int cnt)
{
	int i, j, key, pos;

	for(j = 1; j < cnt; ++j) {
		pos = binary_search(arr, 0, j - 1, key = arr[j]);

		for(i = j - 1; i >= pos; --i)
			arr[i + 1] = arr[i];

		arr[i + 1] = key;
	}
}

void list_print(int *arr, int cnt)
{
	int i;

	for(i = 0; i < cnt; ++i)
		printf("%d ", arr[i]);

	printf("\n");
}

int main()
{
	int i, cnt, *arr;

	scanf("%d", &cnt);

	arr = malloc(cnt * sizeof(int));

	for(i = 0; i < cnt; ++i)
		scanf("%d", &arr[i]);

	insertion_sort(arr, cnt);

	list_print(arr, cnt);

	return 0;
}
