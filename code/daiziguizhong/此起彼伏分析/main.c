/*
������һ������A����СΪn������Ԫ�ز�ľ���ֵ����1.�磺 A={4,5,6,5,6,7,8,9,10,9}�� 
���ڣ�����A��Ŀ������t�����ҵ�t��A�е�λ�á��������α��������и��õķ���ô
*/

#include <stdio.h>

#define N 20

int main()
{
	int a[N],i,n,t;
	scanf("%d %d",&n,&t);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	i = 0;
	while(i < n)
	{
		if(a[i] == t)
		{
			printf("[%d %d]\n",i,a[i]);
			i++;
			continue;
		}
		i += (a[i] > t ? a[i] - t : t - a[i]);
	}
	system("pause");
	return 0;
}
