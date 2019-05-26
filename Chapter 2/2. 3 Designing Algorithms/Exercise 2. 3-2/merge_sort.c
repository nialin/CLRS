#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge(int *arr, int low, int mid, int high);
void merge_sort(int *arr, int low, int high);
void list_print(int *arr, int cnt);


void merge(int *arr, int low, int mid, int high)
{
	int i, *left_buf, *right_buf, left, right, left_cnt, right_cnt;

	left_cnt = mid - low + 1;
	right_cnt = high - mid;

	left_buf = malloc(left_cnt * sizeof(int));
	memcpy(left_buf, &arr[low], left_cnt * sizeof(int));

	right_buf = malloc(right_cnt * sizeof(int));
	memcpy(right_buf, &arr[mid + 1], right_cnt * sizeof(int));

	for(i = low, left = 0, right = 0; left < left_cnt && right < right_cnt; )
		arr[i++] = left_buf[left] < right_buf[right] ? left_buf[left++] : right_buf[right++];

	if(left < left_cnt)
		memcpy(&arr[i], &left_buf[left], (left_cnt - left) * sizeof(int));
	else
		memcpy(&arr[i], &right_buf[right], (right_cnt - right) * sizeof(int));
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
