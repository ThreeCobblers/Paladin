/*
����һ���google������־������ô����㷨�ҳ��Ƿ���һ�������ʣ������ֵ�Ƶ��ռ����������һ�����ϣ�
����϶���һ����ռ�����������ô�������㷨�ҵ������ټٶ�������־�����ڴ��е�һ�����飬�ܹ���
O(1)�Ŀռ䣬O(N)ʱ����㷨��
���ý��ۣ���ԭ�������Ƴ�������ͬ��Ԫ�غ���ô��ԭ�����еĶ���Ԫ�����������л��Ƕ���Ԫ��
*/
#include <stdio.h>
#include <assert.h>
#define N 30

int main()
{
	int i,n,k,count;
	int a[N];
	scanf("%d",&n);
	assert(n > 0);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	k = a[0];
	count = 1;
	for(i = 1;i < n;i++)
	{
		if(k != a[i])
		{
			k = (--count ? k : ++count,a[i]); 
		}
		else
		{
			count++;
		}
	}
	printf("%d",k);
	return 0;
}