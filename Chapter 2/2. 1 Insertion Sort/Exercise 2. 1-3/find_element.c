#include <stdio.h>
#include <stdlib.h>


int find_element(const int * arr, int cnt, int tar);


int find_element(const int * arr, int cnt, int tar)
{
	int i;

	for(i = 0; i < cnt && arr[i] != tar; ++i)
		;

	return i < cnt ? i : -1;
}

int main()
{
	int *arr, i, cnt, tar;

	scanf("%d%d", &cnt, &tar);

	arr = malloc(cnt * sizeof(int));

	for(i = 0; i < cnt; ++i)
		scanf("%d", &arr[i]);

	printf("%d\n", find_element(arr, cnt, tar));

	return 0;
}
