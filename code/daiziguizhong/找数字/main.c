/*
��һ�����������У�����һ�����ֳ�����һ�Σ����������ֶ����ó��������Σ��������ķ����ҵ�����һ�ε��Ǹ�����
*/
/* �뷨�������������ö���������ʾ����Ϊÿ�����ֶ����������Σ�����ÿһ�ĺ�Ӧ����3�ı��� + ȱʧ���ֵĶ�Ӧ������λ��Ҫô��0��Ҫô��1
*/

#include <stdio.h>
#define N 20
int get_i(int m,int i)
{
	return (m & (1 << i)) ? 1 : 0;
}
int main()
{
	int i,j,n;
	int a[N];
	int x[32];
	memset(x,0,sizeof(x));
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
		a[i] = a[i] > 0 ? a[i] : 0 - a[i];
	}
	for(i = 0;i < n;i++)
	{
		for(j = 0;j < 32;j++)
		{
			 x[j] += get_i(a[i],j);
		}
	}
	j = 0;
	for(i = 0;i < 32;i++)
	{
		j |= ((x[i] % 3) << i);
	}
	printf("%d\n",j);
	system("pause");
	return 0;
}