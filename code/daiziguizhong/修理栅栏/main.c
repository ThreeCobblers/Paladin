/*
����դ��
Ϊ������դ������Ҫ���ܳ���ľ���ΪN�飬���ȷֱ�ΪL1,L2...LN�����һ���ľ�壬��Ҫһ���Ŀ�����������Ϊľ��ĳ��ȡ�
���磬����Ϊ21��ľ�壬��Ϊ���飬���ȷֱ�Ϊ5��8��8�����°������µ�˳��ݶϣ�
���Ⱦ��21Ϊ13��8�����������Ϊ21
Ȼ����13Ϊ8��5�����������Ϊ13
�ܵĿ���Ϊ34����Ҳ���԰������µ�˳��
���Ⱦ��21Ϊ16��5�����������Ϊ21
Ȼ����16Ϊ8��8�����������Ϊ16
�ܵĿ���Ϊ37����34Ҫ��

�����ǣ�����N���Լ�ÿһ����ĳ��ȡ���α�֤��С�Ŀ������������ø�Ч�ķ�����

�ⷨ������һ�Ź�����������ÿ��ȡ��С���������
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