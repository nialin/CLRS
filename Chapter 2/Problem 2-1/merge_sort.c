#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define K 3


void merge(int *arr, int low, int mid, int high);

void insertion_sort(int *arr, int cnt);
void merge_sort(int *arr, int low, int high);

void list_print(int *arr, int cnt);


void merge(int *arr, int low, int mid, int high)
{
	int i, left, right, *left_buf, *right_buf;

	left = mid - low + 1;
	right = high - mid;

	left_buf = malloc(left * sizeof(int));
	memcpy(left_buf, &arr[low], left * sizeof(int));
	left_buf[left] = INT_MAX;

	right_buf = malloc(right * sizeof(int));
	memcpy(right_buf, &arr[mid + 1], right * sizeof(int));
	right_buf[right] = INT_MAX;

	for(i = low, left = right = 0; i <= high; ++i)
		arr[i] = left_buf[left] < right_buf[right] ? left_buf[left++] : right_buf[right++];
}

void insertion_sort(int *arr, int cnt)
{
	int i, j, key;

	for(j = 1; j < cnt; ++j) {
		for(i = j - 1, key = arr[j]; i >= 0 && key < arr[i]; --i)
			arr[i + 1] = arr[i];

		arr[i + 1] = key;
	}
}

void merge_sort(int *arr, int low, int high)
{
	int mid;

	if(low < high) {
		mid = (low + high) / 2;

		if(mid - low + 1 > K)
			merge_sort(arr, low, mid);
		else
			insertion_sort(&arr[low], mid - low + 1);

		if(high - mid > K)
			merge_sort(arr, mid + 1, high);
		else
			insertion_sort(&arr[mid + 1], high - mid);

		merge(arr, low, mid, high);
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

	merge_sort(arr, 0, cnt - 1);

	list_print(arr, cnt);

	return 0;
}
