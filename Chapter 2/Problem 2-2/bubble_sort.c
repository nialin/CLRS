#include <stdio.h>
#include <stdlib.h>


void exchange(int *a, int *b);
void bubble_sort(int *arr, int cnt);
void list_print(int *arr, int cnt);


void exchange(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
 * BUBBLE-SORT(A)
 *		for i <- 1 to length[A]
 *			do for j <- length[A] downto i + 1
 *				do if A[j] < A[j - 1]
 *					then exchange A[j] <-> A[j - 1]
 */
void bubble_sort(int *arr, int cnt)
{
	int i, j;

	for(i = 0; i < cnt; ++i)
		for(j = cnt - 1; j > i ; --j)
			if(arr[j] < arr[j - 1])
				exchange(&arr[j], &arr[j - 1]);
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
	int *arr, i, cnt;

	scanf("%d", &cnt);

	arr = malloc(cnt * sizeof(int));

	for(i = 0; i < cnt; ++i)
		scanf("%d", &arr[i]);

	bubble_sort(arr, cnt);

	list_print(arr, cnt);

	return 0;
}
