/*
����δ��������飬����������ҵ���ĵȲ����С�
˼�룺
����Ҫ��֤���ֵ�˳����ԭ������һ�£�����ҵ���ĵȲ������أ�ԭ��������������ģ�
�����ȶ���������������յ�һ��������֮�����е������С�Ȼ�����ǲ��ö�̬�滮�ķ�
�����������⡣���Ǽ���dp[i][j]��ʾ��A[i]A[j]��ʼ�����еĳ��ȣ�dp[i][j]��α�ʾ�أ�
dp[i][j]=dp[j][k]+1���� A[j]-A[i]=A[k]-A[j],��A[k]+A[i]=2*A[j]������dp[i][j]�Ķ��壬
����֪��dp[x][n-1]=2��Ҳ���� ���һ����2������ֻ��A[x]��A[n-1]����Ԫ�ء����ȣ�j��n-2��
��ʼ��ǰ����������ÿһ�����ҵ�i��k������ A[k]+A[i]=2*A[j]������dp[i][j]=dp[j][k]+1��
��û�У���dp[i][j]��Ϊ2.
������i��k����һ��С���ɣ����£���ʼi=j-1,k=j+1��Ȼ��ֱ������߱��������A[k]+A[i]2*A[j]��i--
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