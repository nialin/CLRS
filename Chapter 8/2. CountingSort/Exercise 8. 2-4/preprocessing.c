#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define NUM_RANGE	(1024)


int main(int argc, char *argv[])
{
	int i, cnt, down_range, up_range, *arr, cnts[NUM_RANGE] = {0};

	scanf("%d%d%d", &cnt, &down_range, &up_range);

	if(!(arr = malloc(cnt * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnt; ++i)
		scanf("%d", &arr[i]);

	for(i = 0; i < cnt; ++i)
		++cnts[arr[i]];

	for(i = 1; i < NUM_RANGE; ++i)
		cnts[i] += cnts[i - 1];

	printf("There are %d elems in [%d, %d].\n", cnts[up_range] - cnts[down_range - 1], down_range, up_range);

	free(arr);

	return EXIT_SUCCESS;
}
