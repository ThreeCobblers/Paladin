/*
原题：
N个孩子站成一排，每个人分给一个权重。按照如下的规则分配糖果： 每个孩子至少有一个糖果；所分配权重较高的孩子，
会比他的邻居获得更多的糖果。 问题是，最少需要多少个糖果？
*/
#include <stdio.h>
#define N 30
int redundancy(int a[],int n);
int main()
{
	int i,j,n,num,count,count1,count2;
	int a[N];
	num = 0;
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i = 0;i < n;i++)
	{
		count = count1 = count2 = 0;
		j = i;
		while(a[j] > a[j - 1] && j > 0)
		{
			count1++;
			j--;
		}
		j = i;
		while(a[j] > a[j + 1] && j < n - 1)
		{
			count2++;
			j++;
		}
		count = count1 > count2 ? count1 : count2;
		count++;
		num += count;
		printf("%d ",count);
	}
	printf("\n%d\n",num);
	printf("%d\n",redundancy(a,n));
	return 0;
}
//比起主函数直接计算，增加了O(2*n)的空间复杂度，但是时间复杂度降为O(n)
int redundancy(int a[],int n)
{
	//L[i]表示到a[i - 1]为止递增元素的数量，R[i]表示从a[i + 1]开始递增元素的数量
	int L[N],R[N];
	int i,sum = 0;
	memset(L,0,sizeof(L));
	memset(R,0,sizeof(R));
	L[0] = 1;
	for(i = 1;i < n;i++)
	{
		if(a[i] > a[i - 1])
		{
			L[i] = L[i - 1] + 1;
		}
		else
		{
			L[i] = 1;
		}
	}
	R[n - 1] = 1;
	for(i = n - 2;i >= 0;i--)
	{
		if(a[i] > a[i + 1])
		{
			R[i] = R[i + 1] + 1;
		}
		else
		{
			R[i] = 1;
		}
	}
	for(i = 0;i < n;i++)
	{
		sum += L[i] > R[i] ? L[i] : R[i];
	}
	return sum;
}