/*
问题：
给定长度为n的整数数列：a0,a1,..,an-1，以及整数S。
这个数列会有连续的子序列的整数总和大于S的，求这些数列中，最小的长度。

假设整数均为正，则存在O(n)解法，利用前n项和的递增性质
*/
#include <stdio.h>
int main()
{
	int i,j,n,s,a[20],ls;
	scanf("%d %d",&n,&s);
	a[0] = 0;
	ls = 0x7fffffff;
	for(i = 1;i <= n;i++)
	{
		scanf("%d",&a[i]);
		a[i] += a[i - 1];
	}

	i = 0,j = 0;
	while(j <= n)
	{
		do
		{
			j++;
		}while(a[j] - a[i] < s);
		if(j > n)
		{
			break;
		}
		ls = j - i < ls ? j - i : ls;
		do
		{
			i++;
		}while(a[j] - a[i] > s);
		ls = j - i + 1 < ls ? j - i + 1 : ls;
	}
	printf("%d\n",ls);
	system("pause");
	return 0;
}