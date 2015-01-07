/*
����һ��������������飬��ô�ҵ���һ������0�Ҳ��ڴ������е����֣�����{1,2,0}����3;{3,4,-1,1}����2
�����O(1)�Ŀռ䣬O(n)ʱ��
�뷨����������Ҫ�ҵ�����֮ǰ�����ֶ��ŵ���Ӧ�����±��λ��
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