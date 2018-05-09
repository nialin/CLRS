#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define DEBUG	(1)


#if DEBUG
int cmp_cnts;
#endif

int *prois, proi, init_proi;

void exchange(void *a, void *b, int size);

int partition(void *base, int size, int low, int high, int (*compar)(const void *, const void *));
int random_partition(void *base, int size, int low, int high, int (*compar)(const void *, const void *));

void _quick_sort(void *base, int size, int low, int high, int (*compar)(const void *, const void *));
void quick_sort(void *base, int nmemeb, int size, int (*compar)(const void *, const void *));

void list_show(int *arr, int cnts);

int proi_cmp(const void *px, const void *py);
int val_cmp(const void *a, const void *b);
int *qsort_adversary(int *arr, int cnts);


void exchange(void *a, void *b, int size)
{
	void *tmp;

	if(!(tmp = malloc(size)))
		exit(ENOMEM);

	memcpy(tmp, a, size);
	memcpy(a, b, size);
	memcpy(b, tmp, size);

	free(tmp);
}

int partition(void *base, int size, int low, int high, int (*compar)(const void *, const void *))
{
	int i, j;

	for(i = j = low; i < high; ++i)
		if(compar(base + i * size, base + high * size) < 0) {
			exchange(base + i * size, base + j * size, size);
			++j;
		}

	exchange(base + j * size, base + high * size, size);

	return j;
}

int random_partition(void *base, int size, int low, int high, int (*compar)(const void *, const void *))
{
	int i, j;

	srand(2018);
	exchange(base + (rand() % (high - low + 1) + low) * size, base + high * size, size);

	for(i = j = low; i < high; ++i)
		if(compar(base + i * size, base + high * size) < 0) {
			exchange(base + i * size, base + j * size, size);
			++j;
		}

	exchange(base + j * size, base + high * size, size);

	return j;
}

void _quick_sort(void *base, int size, int low, int high, int (*compar)(const void *, const void *))
{
	int mid;

	if(low < high) {
		mid = partition(base, size, low, high, compar);

		_quick_sort(base, size, low, mid - 1, compar);
		_quick_sort(base, size, mid + 1, high, compar);
	}
}

void quick_sort(void *base, int nmemeb, int size, int (*compar)(const void *, const void *))
{
	_quick_sort(base, size, 0, nmemeb - 1, compar);
}

void list_show(int *arr, int cnts)
{
	int i;

	for(i = 0; i < cnts; ++i)
		printf("%d ", arr[i]);

	printf("\n");
}

int proi_cmp(const void *px, const void *py)
{
	static int candidate = -1;
	const int x = *(const int *)px, y = *(const int *)py;

	if(x == init_proi && y == init_proi) {
		if(x == candidate)
			prois[x] = proi++;
		else
			prois[y] = proi++;
	}

	if(x == init_proi)
		candidate = x;
	else if(y == init_proi)
		candidate = y;

	return prois[x] - prois[y];
}

int val_cmp(const void *a, const void *b)
{
#if DEBUG
	++cmp_cnts;
#endif

	return *(int *)a - *(int *)b;
}

int *qsort_adversary(int *arr, int cnts)
{
	int *seq, *rslt, i;

	if(!(seq = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	if(!(prois = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	if(!(rslt = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	init_proi = cnts - 1;

	for(i = 0; i < cnts; ++i) {
		seq[i] = i;
		prois[i] = init_proi;
	}

	quick_sort(seq, cnts, sizeof(int), proi_cmp);
	quick_sort(arr, cnts, sizeof(int), val_cmp);

	for(i = 0; i < cnts; ++i)
		rslt[seq[i]] = arr[i];

	free(seq);
	free(prois);

	return rslt;
}

int main(int argc, char *argv[])
{
	int *arr, *adversary, i, cnts;

	scanf("%d", &cnts);

	if(!(arr = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &arr[i]);

	adversary = qsort_adversary(arr, cnts);
	list_show(adversary, cnts);

#if DEBUG
	cmp_cnts = 0;
	quick_sort(adversary, cnts, sizeof(int), val_cmp);
	printf("Compare %d times.\n", cmp_cnts);
	list_show(adversary, cnts);
#endif

	free(arr);
	free(adversary);

	return EXIT_SUCCESS;
}
