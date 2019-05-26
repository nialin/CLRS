#include <stdio.h>
#include <stdlib.h>


void insert(int *arr, int cnt, int e);
void insertion_sort(int *arr, int cnt);

void list_print(int *arr, int cnt);


/*
 * INSERT(A, n, e)
 *	for i <- n to 1 and A[i] > e
 *		do A[i + 1] <- A[i]
 * 	A[i + 1] <- e
 */
void insert(int *arr, int cnt, int e)
{
	int i;

	for(i = cnt - 1; i >= 0 && arr[i] > e; --i)
		arr[i + 1] = arr[i];

	arr[i + 1] = e;
}

/*
 * INSERTION-SORT(A, n)
 *	if n > 1
 *		then INSERTION-SORT(A, n - 1)
 *			 INSERT(A, n - 1, A[n])
 */
void insertion_sort(int *arr, int cnt)
{
	if(cnt > 1) {
		insertion_sort(arr, cnt - 1);
		insert(arr, cnt - 1, arr[cnt - 1]);
	}
}

void list_print(int *arr, int cnt)
{
	int i;

	for(i = 0; i < cnt; ++i)
		printf("%d ", arr[i]);

	printf("\n");
}

int main(int argc, char *argv[])
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
