/*
�ܳ������
ԭ��
n�����Ȳ�һ�Ĺ��ӣ��ж��Ƿ����������ӿ��Թ��������Σ������ҵ��ܳ����������
���������� a > b > c > d > e > f > g
���a c g���������Σ���ôa b c�϶��๹��������
*/
#include <stdio.h>
#include <stdlib.h>
#define N 30
int cmp(const void *a,const void *b)
{
	return *(int *)a - *(int *)b;
}
int main()
{
	int n,i;
	int d[N];
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&d[i]);
	}
	qsort(d,n,sizeof(int),cmp);
	for(i = n - 1;i > 2;i--)
	{
		if(d[i - 1] + d[i - 2] > d[i])
		{
			break;
		}
	}
	if(i <= 2)
	{
		printf("can not construct a stringle!\n");
		return 1;
	}
	printf("%d\n",d[i] + d[i - 1] + d[i - 2]);
	return 0;
}
