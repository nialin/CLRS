/*
 * How IBM made its money.
 * Punch card readers for census tabulation in early 1900's.
 * Card sorters, worked on one column at a time.
 * It's the algorithm for using the machine that extends the technique to multi-column sorting.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#define RADIX		(0x100)
#define DIGIT_BIT	(8)
#define DIGIT_CNT	(32 / DIGIT_BIT)


void radix_sort(uint32_t *arr, int cnt);

void list_show(uint32_t *arr, int cnt);


void radix_sort(uint32_t *arr, int cnt)
{
	int i, j;
	uint32_t cnts[RADIX] = {0}, *tmp;

	if(!(tmp = malloc(cnt * sizeof(uint32_t))))
		exit(ENOMEM);

	for(i = 0; i < DIGIT_CNT; ++i) {
		memset(cnts, 0, sizeof(cnts));
		memcpy(tmp, arr, cnt * sizeof(uint32_t));

		for(j = 0; j < cnt; ++j)
			++cnts[tmp[j] >> i * DIGIT_BIT & (RADIX - 1)];

		for(j = 1; j < RADIX; ++j)
			cnts[j] += cnts[j - 1];

		for(j = cnt - 1; j >= 0; --j)
			arr[--cnts[tmp[j] >> i * DIGIT_BIT & (RADIX - 1)]] = tmp[j];
	}

	free(tmp);
}

void list_show(uint32_t *arr, int cnt)
{
	int i;

	for(i = 0; i < cnt; ++i)
		printf("%d ", arr[i]);

	printf("\n");
}

int main(int argc, char *argv[])
{
	int i, cnt;
	uint32_t *arr;

	scanf("%d", &cnt);

	if(!(arr = malloc(cnt * sizeof(uint32_t))))
		exit(ENOMEM);

	for(i = 0; i < cnt; ++i)
		scanf("%u", &arr[i]);

	radix_sort(arr, cnt);

	list_show(arr, cnt);

	free(arr);

	return EXIT_SUCCESS;
}
