#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int binary_search(int *arr, int low, int high, int v);

void list_show(int *arr, int cnt);

int compare(const void *a, const void *b);


/*
 * BINARY_SEARCH(A, low, high, v)
 *		while low <= high
 *			do 	mid <- (low + high) / 2
 *				if A[mid] = v
 *					then return mid
 *				if A[mid] < v
 *					then low = mid + 1
 *					else high = mid - 1
 *		return NIL
 */
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

void list_show(int *arr, int cnt)
{
	int i;

	for(i = 0; i < cnt; ++i)
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
	int *arr, i, cnt, v;

	scanf("%d", &cnt);

	if(!(arr = malloc(cnt * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnt; ++i)
		scanf("%d", &arr[i]);

	qsort(arr, cnt, sizeof(int), compare);

	list_show(arr, cnt);

	while(scanf("%d", &choice) != EOF && 1 == choice) {
		scanf("%d", &v);
		rslt = binary_search(arr, 0, cnt - 1, v);

		if(-1 == rslt)
			printf("%d is not found.\n", v);
		else
			printf("%d is found, its pos is %d.\n", v, rslt);
	}

	free(arr);

	return EXIT_SUCCESS;
}
