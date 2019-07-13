#include <stdio.h>
#include <stdlib.h>


struct station {
	int cost, trans, par;
};


void print_station(struct station *s0, struct station *s1, int n, int par);


void print_station(struct station *s0, struct station *s1, int n, int par)
{
	int i, top = 0, *stack = malloc(n * sizeof(int));

	for(i = n - 1; i >= 0; --i){
		stack[top++] = par;
		par = 1 == par ? s0[i].par : s1[i].par;
	}

	for(i = 0; i < n; ++i)
		printf("Line %d Station %d\n", stack[--top], i);
}

int main()
{
	struct station *s0, *s1;
	int i, n, f[2][2];

	scanf("%d", &n);

	s0 = malloc(n * sizeof(struct station));
	s1 = malloc(n * sizeof(struct station));

	scanf("%d%d", &f[0][0], &f[1][0]);

	for(i = 0; i < n; ++i)
		scanf("%d %d", &s0[i].cost, &s0[i].trans);

	for(i = 0; i < n; ++i)
		scanf("%d %d", &s1[i].cost, &s1[i].trans);

	f[0][0] += s0[0].cost;
	f[1][0] += s1[0].cost;

	for(i = 1; i < n; ++i) {
		if(f[0][0] < f[1][0] +  s1[i - 1].trans) {
			f[0][1] = f[0][0] + s0[i].cost;
			s0[i].par = 1;
		}
		else {
			f[0][1] = f[1][0] + s1[i - 1].trans + s0[i].cost;
			s0[i].par = 2;
		}

		if(f[1][0] < f[0][0] + s0[i - 1].trans) {
			f[1][1] = f[1][0] + s1[i].cost;
			s1[i].par = 2;
		}
		else {
			f[1][1] = f[0][0] + s0[i - 1].trans + s1[i].cost;
			s1[i].par = 1;
		}

		f[0][0] = f[0][1];
		f[1][0] = f[1][1];
	}

	if(f[0][0] + s0[n - 1].trans < f[1][0] + s1[n - 1].trans)
		print_station(s0, s1, n, 1);
	else
		print_station(s0, s1, n, 2);

	return 0;
}
