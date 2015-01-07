/*今日面试题：相伴一生

给定一个数组，数组中只包含0和1。请找到一个最长的子序列，其中0和1的数量是相同的。

例1：10101010 结果就是其本身。

例2：1101000 结果是110100

请大家展开自己的思路。
*/
/*
分析：
将0改为-1，d[k]表示a[0,k]之和，那么当d[m] = d[n]时可知m + 1到n满足条件，当然，这种方法无法计算从头开始的情况，所以要另作考虑
*/

#include <stdio.h>
#define N 20
//tmap结构保存dp数组中相同值 最早开始最后结束两个位置
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
			max = i + 1;//保存从头开始情况的最大值
		}
	}
	//计算非从头开始情况的最大值
	for(i = 0;i < n;i++)
	{
		switch(map[dp[i]].f)
		{
		case 0:
			map[dp[i] % (2 * N)].f++;//取模是为了能够处理负数
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