/*
修理栅栏
为了修理栅栏，需要将很长的木板锯为N块，长度分别为L1,L2...LN。锯断一块儿木板，需要一定的开销，开销记为木板的长度。
例如，长度为21的木板，锯为三块，长度分别为5，8，8。如下按照如下的顺序据断：
首先锯断21为13和8两块儿，开销为21
然后锯断13为8和5两块儿，开销为13
总的开销为34。但也可以按照如下的顺序：
首先锯断21为16和5两块儿，开销为21
然后锯断16为8和8两块儿，开销为16
总的开销为37。比34要大。

问题是，给定N，以及每一块儿的长度。如何保证最小的开销。尽量采用高效的方法。

解法：构造一颗哈夫曼树，即每次取最小的两段相加
*/
#include <stdio.h>
#include <stdlib.h>
#define N 20
int cacu(int a[],int n);
int theLastTwoSmall(int a[],int n);
void swap(int *a,int *b);
int main()
{
	int a[N];
	int i,n,m;
	scanf("%d %d",&n,&m);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	i = cacu(a,n);
	printf("%d\n",i);
	return 0;
}
int cacu(int a[],int n)
{
	if(n == 1)
	{
		return a[0];
	}
	else if(n == 2)
	{
		return a[0] + a[1];
	}
	else
	{
		return theLastTwoSmall(a,n) + cacu(a,n - 1);
	}
}
int theLastTwoSmall(int a[],int n)
{
	int i;
	for(i = 0;i < n - 1;i++)
	{
		if(a[i] < a[i + 1])
		{
			swap(&a[i],&a[i + 1]);
		}
	}
	for(i = 0;i < n - 2;i++)
	{
		if(a[i] < a[i + 1])
		{
			swap(&a[i],&a[i + 1]);
		}
	}
	a[n - 2] = a[n - 1] + a[n - 2];
	return a[n - 2];
}
void swap(int *a,int *b)
{
	int i = *a;
	*a = *b;
	*b = i;
}