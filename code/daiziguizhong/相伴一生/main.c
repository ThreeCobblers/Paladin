/*���������⣺���һ��

����һ�����飬������ֻ����0��1�����ҵ�һ����������У�����0��1����������ͬ�ġ�

��1��10101010 ��������䱾��

��2��1101000 �����110100

����չ���Լ���˼·��
*/
/*
������
��0��Ϊ-1��d[k]��ʾa[0,k]֮�ͣ���ô��d[m] = d[n]ʱ��֪m + 1��n������������Ȼ�����ַ����޷������ͷ��ʼ�����������Ҫ��������
*/

#include <stdio.h>
#define N 20
//tmap�ṹ����dp��������ֵͬ ���翪ʼ����������λ��
typedef struct node
{
	int s;
	int e;
	int f;
}tmap;
int main()
{
	int i,n,num = 0,max = 0;
	int a[N];
	int dp[N];
	tmap map[N * 2];
	scanf("%d",&n);
	memset(map,0,sizeof(map));
	memset(dp,0,n * sizeof(int));
	for(i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
		a[i] = a[i] ? a[i] : -1;
		num += a[i];
		dp[i] = num;
		if(dp[i] == 0)
		{
			max = i + 1;//�����ͷ��ʼ��������ֵ
		}
	}
	//����Ǵ�ͷ��ʼ��������ֵ
	for(i = 0;i < n;i++)
	{
		switch(map[dp[i]].f)
		{
		case 0:
			map[dp[i] % (2 * N)].f++;//ȡģ��Ϊ���ܹ�������
			map[dp[i] % (2 * N)].s = i;
			break;
		case 1:
			map[dp[i] % (2 * N)].f++;
			map[dp[i] % (2 * N)].e = i;
			break;
		case 2:
			map[dp[i] % (2 * N)].e = i;
			max = max > map[dp[i] % (2 * N)].e - map[dp[i] % (2 * N)].s ? max : map[dp[i] % (2 * N)].e - map[dp[i] % (2 * N)].s;
			break;
		default:break;
		}
	}
	printf("%d\n",max);
	return 0;
}