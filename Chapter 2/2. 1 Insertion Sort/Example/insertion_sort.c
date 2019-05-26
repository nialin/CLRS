#include <stdio.h>
#include <stdlib.h>


void insertion_sort(int *arr, int cnt);
void list_print(int *arr, int cnt);


void insertion_sort(int *arr, int cnt)
{
	int i, j, key;

	for(j = 1; j < cnt; ++j) {
		for(i = j - 1, key = arr[j]; i >= 0 && arr[i] > key; --i)
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
