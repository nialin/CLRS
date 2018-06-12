#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>


void merge(int *arr, int low, int mid, int high);
void merge_sort(int *arr, int low, int high);

void k_sorted(int *arr, int cnt, int k);

void list_show(int *arr, int cnt);


void merge(int *arr, int low, int mid, int high)
{
	int i, cnt_1, cnt_2, *tmp_1, *tmp_2, index_1, index_2;

	cnt_1 = mid - low + 1;
	cnt_2 = high - mid;

	if(!(tmp_1 = malloc((cnt_1 + 1) * sizeof(int))))
		exit(ENOMEM);

	if(!(tmp_2 = malloc((cnt_2 + 1) * sizeof(int))))
		exit(ENOMEM);

	memcpy(tmp_1, &arr[low], cnt_1 * sizeof(int));
	memcpy(tmp_2, &arr[mid + 1], cnt_2 * sizeof(int));

	tmp_1[cnt_1] = INT_MAX;
	tmp_2[cnt_2] = INT_MAX;

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

void k_sorted(int *arr, int cnt, int k)
{
	int i, j, *tmp;

	if(!(tmp = malloc((cnt / k + 1) * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < k; ++i) {
		for(j = 0; j * k + i < cnt; ++j)
			tmp[j] = arr[j * k + i];

		merge_sort(tmp, 0, j - 1);

		for(j = 0; j * k + i < cnt; ++j)
			arr[j * k + i] = tmp[j];
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
	int i, k, cnt, *arr;

	scanf("%d%d", &cnt, &k);

	if(!(arr = malloc(cnt * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnt; ++i)
		scanf("%d", &arr[i]);

	k_sorted(arr, cnt, k);

	list_show(arr, cnt);

	free(arr);

	return EXIT_SUCCESS;
}
