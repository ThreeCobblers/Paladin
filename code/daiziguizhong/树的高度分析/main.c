/*
���ĸ߶ȷ���
��һ����������һ���Ƕ���������n���ڵ㣬���Ϊ0��n-1����һ������A�����������Ϊ0��n-1��
�����ֵA[i]��ʾ�ڵ�i�ĸ��ڵ��id�����ڵ�ĸ��ڵ�idΪ-1����������A��������ĸ߶ȡ� 
���������Ŀ�������Ȱ�����д������Ȼ���һ���������ͺ������ˣ��������ӣ� 333-1201234
*/
#include <stdio.h>

#define N 20
int b[N];//���������м�������������ظ�����
int heighOfTree(int a[],int i); 
int main()
{
	int a[N];
	int i,n,max = -1;
	memset(b,0,sizeof(b));
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i = 0;i < n;i++)
	{
		max = max > heighOfTree(a,i) ? max : heighOfTree(a,i);
	}
	printf("%d\n",max);
	return 0;
}
//�ݹ飬֪���������ڵ�-1�������Ѿ�������Ľڵ�
int heighOfTree(int a[],int i)
{
	if(a[i] == -1)
	{
		return 1;
	}
	else if(b[i])
	{
		return b[i];
	}
	else
	{
		b[i] = 1 + heighOfTree(a,a[i]);
		return b[i];
	}
}