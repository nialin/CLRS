#include <stdio.h>
#include <stdlib.h>


int binary_search(int *arr, int low, int high, int v);

void list_print(int *arr, int cnt);

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

int compare(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int main()
{
	int i, cnt, v, *arr;

	scanf("%d%d", &cnt, &v);

	arr = malloc(cnt * sizeof(int));

	for(i = 0; i < cnt; ++i)
		scanf("%d", &arr[i]);

	qsort(arr, cnt, sizeof(int), compare);

	printf("%d is%s found.\n", v, -1 == binary_search(arr, 0, cnt - 1, v) ? "n't" : "");

	return 0;
}
