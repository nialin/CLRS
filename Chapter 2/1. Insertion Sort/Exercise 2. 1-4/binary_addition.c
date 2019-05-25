#include <stdio.h>
#include <stdlib.h>


char *binary_create(int n);
char *binary_addition(const char *a, const char *b, int n);


char *binary_create(int n)
{
	char *rslt;

	rslt = malloc(n + 1);
	scanf("%s", rslt);

	return rslt;
}

char *binary_addition(const char *a, const char *b, int n)
{
	int i;
	char *rslt, flg;

	rslt = malloc(n + 2);

	for(i = n, flg = 0; i > 0; --i) {
		rslt[i] = (((a[i - 1] - '0') + (b[i - 1] - '0') + flg) & 1) + '0';
		flg = ((a[i - 1] - '0') + (b[i - 1] - '0')) >> 1;
	}

	rslt[0] = flg + '0';
	rslt[n + 1] = 0;

	return rslt;
}

int main()
{
	int n;
	char *a, *b, *c;

	scanf("%d", &n);

	a = binary_create(n);
	b = binary_create(n);
	c = binary_addition(a, b, n);

	printf("%s\n", c);

	return 0;
}
