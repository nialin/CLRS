#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void insertion_sort(int *arr, int cnt);
void list_show(int *arr, int cnt);


void insertion_sort(int *arr, int cnt)
{
	int i, j, key;

	for(j = 1; j < cnt; ++j) {
		for(i = j - 1, key = arr[j]; i >= 0 && arr[i] > key; --i)
			arr[i + 1] = arr[i];

		arr[i + 1] = key;
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

	insertion_sort(arr, cnt);

	list_show(arr, cnt);

	free(arr);

	return EXIT_SUCCESS;
}
