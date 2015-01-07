/*
数组统计分析

给定数组A，大小为n，数组元素为1到n的数字，不过有的数字出现了多次，有的数字没有出现。
请给出算法和程序，统计哪些数字没有出现，哪些数字出现了多少次。能够在O(n)的时间复杂度，O(1)的空间复杂度要求下完成么?
*/
#include <stdio.h>
#define N 20

int main()
{
	int a[N];
	int i,n;
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i = 0;i < n;i++)
	{
		a[a[i] % n] += n;
	}
	for(i = 0;i < n;i++)
	{
		printf("[%d %d]\n",i,a[i] / n);
	}
	return 0;
}