#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LARGE_PRIME	(49999)


static int rf_1, rf_2;

void hash_func_init(void);
int hash_func_universal(int key);


void hash_func_init(void)
{
	srand(time(NULL));

	rf_1 = rand() % LARGE_PRIME;
	rf_2 = rand() % (LARGE_PRIME - 1) + 1;
}

int hash_func_universal(int key)
{
	return (rf_1 * key + rf_2) % LARGE_PRIME;
}

int main(int argc, char *argv[])
{
	int i, cnt, max, key;

	hash_func_init();

	scanf("%d%d", &cnt, &max);

	for(i = 0; i < cnt; ++i) {
		scanf("%d", &key);

		printf("HASH[%d] = %d\n", key, hash_func_universal(key) % max);
	}

	return EXIT_SUCCESS;
}
