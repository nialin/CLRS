#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define TRUE	(1 == 1)
#define FALSE	(!TRUE)



int binary_search(int *arr, int low, int high, int v);

int compare(const void *a, const void *b);

int two_sum(int *arr, int cnts, int x);


int binary_search(int *arr, int low, int high, int v)
{
	int mid;

	while(low <= high) {
		mid = (low + high) / 2;

		if(arr[mid] == v)
			return mid;

		if(arr[mid] < v)
			low = mid + 1;
		else
			high = mid - 1;
	}

	return -1;
}

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

/*
 * TWO_SUM(S, x)
 * 		SORT(S)
 *		for i <- 1 to length[S]
 *			do if BINARY_SEARCH(A, 1, length[S], x - A[i]) != NIL
 *					then return TRUE
 *		return FALSE
 **/
int two_sum(int *arr, int cnts, int x)
{
	int i;

	qsort(arr, cnts, sizeof(int), compare);

	for(i = 0; i < cnts; ++i)
		if(binary_search(arr, 0, cnts - 1, x - arr[i]) != -1)
			return TRUE;

	return FALSE;
}

int main(int argc, char *argv[])
{
	int *arr, i, cnts, x;

	scanf("%d%d", &cnts, &x);

	if(!(arr = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &arr[i]);

	printf("%s\n", two_sum(arr, cnts, x) ? "Exist" : "Not Exist");

	free(arr);

	return EXIT_SUCCESS;
}
