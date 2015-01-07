/*
周长最长分析
原题
n根长度不一的棍子，判断是否有三根棍子可以构成三角形，并且找到周长最长的三角形
分析：假设 a > b > c > d > e > f > g
如果a c g构成三角形，那么a b c肯定亦构成三角形
*/
#include <stdio.h>
#include <stdlib.h>
#define N 30
int cmp(const void *a,const void *b)
{
	return *(int *)a - *(int *)b;
}
int main()
{
	int n,i;
	int d[N];
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&d[i]);
	}
	qsort(d,n,sizeof(int),cmp);
	for(i = n - 1;i > 2;i--)
	{
		if(d[i - 1] + d[i - 2] > d[i])
		{
			break;
		}
	}
	if(i <= 2)
	{
		printf("can not construct a stringle!\n");
		return 1;
	}
	printf("%d\n",d[i] + d[i - 1] + d[i - 2]);
	return 0;
}
