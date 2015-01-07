/*
给你一天的google搜索日志，你怎么设计算法找出是否有一个搜索词，他出现的频率占所有搜索的一半以上？
如果肯定有一个词占大多数，你怎么提高你的算法找到它？再假定搜索日志就是内存中的一个数组，能够有
O(1)的空间，O(N)时间的算法？
利用结论：在原序列中移除两个不同的元素后，那么在原序列中的多数元素在新序列中还是多数元素
*/
#include <stdio.h>
#include <assert.h>
#define N 30

int main()
{
	int i,n,k,count;
	int a[N];
	scanf("%d",&n);
	assert(n > 0);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	k = a[0];
	count = 1;
	for(i = 1;i < n;i++)
	{
		if(k != a[i])
		{
			k = (--count ? k : ++count,a[i]); 
		}
		else
		{
			count++;
		}
	}
	printf("%d",k);
	return 0;
}