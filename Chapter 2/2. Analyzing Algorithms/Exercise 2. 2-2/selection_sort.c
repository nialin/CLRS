#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void selection_sort(int *arr, int cnt);
void list_show(int *arr, int cnt);


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

	selection_sort(arr, cnt);

	list_show(arr, cnt);

	free(arr);

	return EXIT_SUCCESS;
}
