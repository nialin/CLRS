#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STR_MAX_SIZE	(100)


int main(int argc, char *argv[])
{
	char (*strs)[STR_MAX_SIZE], (*tmp)[STR_MAX_SIZE];
	int i, j, str_cnt, max_len = 0, cnts[128] = {0};

	scanf("%d", &str_cnt);

	if(!(strs = malloc(str_cnt * sizeof(char [STR_MAX_SIZE]))))
		exit(ENOMEM);

	if(!(tmp = malloc(str_cnt * sizeof(char [STR_MAX_SIZE]))))
		exit(ENOMEM);

	for(i = 0; i < str_cnt; ++i) {
		memset(strs[i], 0 , STR_MAX_SIZE);

		scanf("%s", strs[i]);

		if(max_len < strlen(strs[i]))
			max_len = strlen(strs[i]);
	}

	/* Radix Sort */
	for(i = max_len - 1; i >= 0; --i) {
		memset(cnts, 0, sizeof(cnts));
		memcpy(tmp, strs, str_cnt * sizeof(char [STR_MAX_SIZE]));

		for(j = 0; j < str_cnt; ++j)
			++cnts[tmp[j][i]];

		for(j = 1; j < 128; ++j)
			cnts[j] += cnts[j - 1];

		for(j = str_cnt - 1; j >= 0; --j)
			strcpy(strs[--cnts[tmp[j][i]]], tmp[j]);
	}

	for(i = 0; i < str_cnt; ++i)
		printf("%s\n", strs[i]);

	free(strs);
	free(tmp);

	return EXIT_SUCCESS;
}
