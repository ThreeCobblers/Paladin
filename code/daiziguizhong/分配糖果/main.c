/*
ԭ�⣺
N������վ��һ�ţ�ÿ���˷ָ�һ��Ȩ�ء��������µĹ�������ǹ��� ÿ������������һ���ǹ���������Ȩ�ؽϸߵĺ��ӣ�
��������ھӻ�ø�����ǹ��� �����ǣ�������Ҫ���ٸ��ǹ���
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
//����������ֱ�Ӽ��㣬������O(2*n)�Ŀռ临�Ӷȣ�����ʱ�临�ӶȽ�ΪO(n)
int redundancy(int a[],int n)
{
	//L[i]��ʾ��a[i - 1]Ϊֹ����Ԫ�ص�������R[i]��ʾ��a[i + 1]��ʼ����Ԫ�ص�����
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