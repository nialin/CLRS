#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>


int merge_inversion(int *arr, int low, int mid, int high);
int inversion(int *arr, int low, int high);


int merge_inversion(int *arr, int low, int mid, int high)
{
	int i, rslt = 0;
	int *left, *right, len_1, len_2, index_1, index_2;

	len_1 = mid - low + 1;
	len_2 = high - mid;

	if(!(left = malloc((len_1 + 1) * sizeof(int))))
		exit(ENOMEM);

	if(!(right = malloc((len_2 + 1) * sizeof(int))))
		exit(ENOMEM);

	memcpy(left, &arr[low], len_1 * sizeof(int));
	memcpy(right, &arr[mid + 1], len_2 * sizeof(int));

	left[len_1] = INT_MAX;
	right[len_2] = INT_MAX;

	for(i = low, index_1 = index_2 = 0; i <= high; ++i) {
		if(left[index_1] <= right[index_2])
			arr[i] = left[index_1++];
		else {
			rslt += len_1 - index_1;
			arr[i] = right[index_2++];
		}
	}

	free(left);
	free(right);

	return rslt;
}

int inversion(int *arr, int low, int high)
{
	int mid, rslt = 0;

	if(low < high) {
		mid = (low + high) / 2;

		rslt += inversion(arr, low, mid);
		rslt += inversion(arr, mid + 1, high);

		rslt += merge_inversion(arr, low, mid, high);
	}

	return rslt;
}

int main(int argc, char *argv[])
{
	int *arr, i, cnts;

	scanf("%d", &cnts);

	if(!(arr = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &arr[i]);

	printf("Inversion = %d\n", inversion(arr, 0, cnts - 1));

	free(arr);

	return EXIT_SUCCESS;
}
