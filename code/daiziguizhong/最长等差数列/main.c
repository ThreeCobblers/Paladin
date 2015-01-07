/*
给定未排序的数组，请给出方法找到最长的等差数列。
思想：
不需要保证数字的顺序与原来数组一致，如何找到最长的等差数列呢？原来的数组是无序的，
我们先对数组进行排序，最终的一定是排序之后序列的子序列。然后，我们采用动态规划的方
法解决这个问题。我们假设dp[i][j]表示以A[i]A[j]开始的数列的长度，dp[i][j]如何表示呢？
dp[i][j]=dp[j][k]+1，当 A[j]-A[i]=A[k]-A[j],及A[k]+A[i]=2*A[j]。根据dp[i][j]的定义，
我们知道dp[x][n-1]=2，也就是 最后一列是2，数列只有A[x]和A[n-1]两个元素。首先，j从n-2，
开始向前遍历，对于每一个，找到i和k，满足 A[k]+A[i]=2*A[j]，则有dp[i][j]=dp[j][k]+1，
若没有，则dp[i][j]就为2.
这里找i和k，有一个小技巧，如下：初始i=j-1,k=j+1，然后分别向两边遍历，如果A[k]+A[i]2*A[j]则i--
*/
#include <stdio.h>
#define N 20
int lengthOfLongestAP(int set[],int n);
int cmp(const void *a,const void *b);
int main()
{
	int set[N];
	int i,n;
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&set[i]);
	}
	qsort(set,sizeof(int),n,cmp);
	printf("%d\n",lengthOfLongestAP(set,n));
	system("pause");
	return 0;
}
int cmp(const void *a,const void *b)
{
	return (int *)a - (int *)b;
}
int lengthOfLongestAP(int set[],int n)
{
	if(n <= 2)
	{
		return n;
	}
	else
	{
		int L[N][N];
		int llap = 2;
		int i,j,k;
		for(i = 0;i < n;i++)
		{
			L[i][n - 1] = 2;
		}
		for(j = n - 2;j >= 1;j--)
		{
			int i = j - 1;
			int k = j + 1;
			while(i >= 0 && k < n)
			{
				if(set[i] + set[k] < 2 * set[j])
				{
					k++;
				}
				else if(set[i] + set[k] > 2 * set[j])
				{
					L[i][j] = 2;
					i--;
				}
				else
				{
					L[i][j] = L[j][k] + 1;
					llap = llap > L[i][j] ? llap : L[i][j];
					i--;
					k++;
				}
			}
			while(i >= 0)
			{
				L[i][j] = 2;
				i--;
			}
		}
		return llap;
	}
}