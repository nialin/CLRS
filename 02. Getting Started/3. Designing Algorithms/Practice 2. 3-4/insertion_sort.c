#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void insert(int *arr, int cnts, int e);
void insertion_sort(int *arr, int cnts);

void list_show(int *arr, int cnts);


/*
 * INSERT(A, n, e)
 *	for i <- n to 1 and A[i] > e
 *		do A[i + 1] <- A[i]
 * 	A[i + 1] <- e
 */
void insert(int *arr, int cnts, int e)
{
	int i;

	for(i = cnts - 1; i >= 0 && arr[i] > e; --i)
		arr[i + 1] = arr[i];

	arr[i + 1] = e;
}

/*
 * INSERTION-SORT(A, n)
 *	if n > 1
 *		then INSERTION-SORT(A, n - 1)
 *			 INSERT(A, n - 1, A[n])
 */
void insertion_sort(int *arr, int cnts)
{
	if(cnts > 1) {
		insertion_sort(arr, cnts - 1);
		insert(arr, cnts - 1, arr[cnts - 1]);
	}
}

void list_show(int *arr, int cnts)
{
	int i;

	for(i = 0; i < cnts; ++i)
		printf("%d ", arr[i]);

	printf("\n");
}

int main(int argc, char *argv[])
{
	int *arr, i, cnts;

	scanf("%d", &cnts);

	if(!(arr = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &arr[i]);

	insertion_sort(arr, cnts);

	list_show(arr, cnts);

	free(arr);

	return EXIT_SUCCESS;
}
