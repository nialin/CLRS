#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


int merge_inversion(int *arr, int low, int mid, int high);
int inversion(int *arr, int low, int high);


int merge_inversion(int *arr, int low, int mid, int high)
{
	int i, *left_buf, *right_buf, left, right, left_cnt, right_cnt, rslt;

	left_cnt = mid - low + 1;
	right_cnt = high - mid;

	left_buf = malloc((left_cnt + 1) * sizeof(int));
	memcpy(left_buf, &arr[low], left_cnt * sizeof(int));
	left_buf[left_cnt] = INT_MAX;

	right_buf = malloc((right_cnt + 1) * sizeof(int));
	memcpy(right_buf, &arr[mid + 1], right_cnt * sizeof(int));
	right_buf[right_cnt] = INT_MAX;

	for(i = low, left = right = 0, rslt = 0; i <= high; ++i) {
		if(left_buf[left] < right_buf[right])
			arr[i] = left_buf[left++];
		else {
			rslt += left_cnt - left;
			arr[i] = right_buf[right++];
		}
	}

	return rslt;
}

int inversion(int *arr, int low, int high)
{
	int mid;

	if(low >= high)
		return 0;

	mid = (low + high) / 2;

	return inversion(arr, low, mid) + inversion(arr, mid + 1, high) + merge_inversion(arr, low, mid, high);
}

int main()
{
	int i, cnt, *arr;

	scanf("%d", &cnt);

	arr = malloc(cnt * sizeof(int));

	for(i = 0; i < cnt; ++i)
		scanf("%d", &arr[i]);

	printf("%d\n", inversion(arr, 0, cnt - 1));

	return 0;
}
