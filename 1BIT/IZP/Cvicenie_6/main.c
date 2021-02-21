#include<stdio.h>

void zamen(int *x, int *y);

int main()
{
	int a = 1;
	int b = 2;
	zamen(&a,&b);
	printf("%d %d\n", a,b);
	return 0;
}

void zamen(int *x, int *y)
{
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}
