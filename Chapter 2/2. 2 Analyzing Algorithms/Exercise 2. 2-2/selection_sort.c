#include <stdio.h>
#include <stdlib.h>


void selection_sort(int *arr, int cnt);
void list_print(int *arr, int cnt);


void selection_sort(int *arr, int cnt)
{
	int i, j, min_pos, tmp;

	for(i = 0; i < cnt - 1; ++i) {
		for(min_pos = i, j = i + 1; j < cnt; ++j) {
			if(arr[j] < arr[min_pos])
				min_pos = j;
		}

		tmp = arr[min_pos];
		arr[min_pos] = arr[i];
		arr[i] = tmp;
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

	selection_sort(arr, cnt);

	list_print(arr, cnt);

	return 0;
}
