/*
给定一个无序的整数数组，怎么找到第一个大于0且不在次数组中的数字，比如{1,2,0}返回3;{3,4,-1,1}返回2
最好用O(1)的空间，O(n)时间
想法：让所有在要找的数字之前的数字都放到对应数组下标的位置
*/
#include <stdio.h>
#define N 20
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
int main()
{
	int a[N];
	int i;
	int n;
	scanf("%d",&n);
	memset(a,0,sizeof(a));
	for(i = 1;i <= n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i = 1;i <= n;i++)
	{
		if(a[i] > 0 && a[i] < i)
		{
			swap(&a[i],&a[a[i]]);
		}
	}
	for(i = 1;i <= n + 1;i++)
	{
		if(a[i] != i)
		{
			printf("%d\n",i);
			break;
		}
	}
	return 0;
}