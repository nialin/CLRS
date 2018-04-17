#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int binary_search(int *arr, int low, int high, int v);

void list_show(int *arr, int cnts);

int compare(const void *a, const void *b);


/*
 * BINARY_SEARCH(A, low, high, v)
 *		if low > high
 *			then return NIL
 *		mid <- (low + high) / 2
 *		if A[mid] = v
 *			then return mid
 *		if A[mid] < v
 *			then return BINARY_SEARCH(A, mid + 1, high, v)
 *			else return BINARY_SEARCH(A, low, mid - 1, v)
 */
int binary_search(int *arr, int low, int high, int v)
{
	int mid;

	if(low > high)
		return -1;

	mid = (low + high) / 2;

	if(arr[mid] == v)
		return mid;

	if(arr[mid] < v)
		return binary_search(arr, mid + 1, high, v);

	return binary_search(arr, low, mid - 1, v);
}

void list_show(int *arr, int cnts)
{
	int i;

	for(i = 0; i < cnts; ++i)
		printf("[%d] %d\n", i, arr[i]);
}

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

/*
 * Debug Format:
 *	Input File:
 *		Function Data
 *		Function :
 *			#1 Search
 *			#0 Exit
 *
 *	Output File:
 *		-Found		: Data is found, its pos is Pos.
 *		-Not Found	: Data is not found.
 */
int main(int argc, char *argv[])
{
	int choice, rslt;
	int *arr, i, cnts, v;

	scanf("%d", &cnts);

	if(!(arr = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &arr[i]);

	qsort(arr, cnts, sizeof(int), compare);

	list_show(arr, cnts);

	while(scanf("%d", &choice) != EOF && 1 == choice) {
		scanf("%d", &v);
		rslt = binary_search(arr, 0, cnts - 1, v);

		if(-1 == rslt)
			printf("%d is not found.\n", v);
		else
			printf("%d is found, its pos is %d.\n", v, rslt);
	}

	free(arr);

	return EXIT_SUCCESS;
}
