/*
���⣺
��������Ϊn���������У�a0,a1,..,an-1���Լ�����S��
������л��������������е������ܺʹ���S�ģ�����Щ�����У���С�ĳ��ȡ�

����������Ϊ���������O(n)�ⷨ������ǰn��͵ĵ�������
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