/*相差甚远
原题
给定一个数组，我们可以找到两个不相交的、并且是连续的子数组A和B，A中的数字和为sum(A), B中的元素和为sum(B)。
找到这样的A和B，满足sum(A) - sum(B)的绝对值是最大的。 例如：[2, -1 -2, 1, -4, 2, 8]划分为A=[-1, -2, 1, -4]
B=[2, 8] 最大的值为16
看到此题，第一感觉是以i为分界点，分别结算两边最大最小值，然后求最大，和陈老师的思路基本一致
*/

/*
自己的代码缺陷，重复代码太多，有空必须重构
*/
#include <stdio.h>
#define N 30
int myfabs(int a,int b,int c,int d)
{

	int e = ((a - b > 0) ? a - b : b - a);
	int f = ((c - d > 0) ? c - d : d - c);
	return e > f ? e : f;
}
int main()
{
	int i,j,n;
	//举例 max_left[i]表示a[0,i]中连续变量的最大和
	//max_right[i]表示a[i,n - 1]中连续变量的最大和
	int a[N],max_left[N],min_left[N],max_right[N],min_right[N];
	int max,max_until[N],min,min_until[N];
	scanf("%d",&n);
	for(i = 0; i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	max_until[0] = a[0];
	max = max_until[0];//max_until表示包含a[0,i]且包含a[i](或者a[i,n - 1]且包含a[i])的最大和
	max_left[0] = max_until[0];
	for(i = 1;i < n;i++)
	{
		if(a[i] + max_until[i - 1] > max_until[i - 1] && a[i] + max_until[i - 1] > a[i])
		{
			max_until[i] = a[i] + max_until[i - 1];
			max = max > max_until[i] ? max : max_until[i];
			max_left[i] = max;
		}
		else
		{
			max_until[i] = a[i];
			max = max > max_until[i] ? max : max_until[i];
			max_left[i] = max;
		}
	}
	min_until[0] = a[0];
	min = min_until[0];//min_until表示包含a[0,i]且包含a[i](或者a[i,n - 1]且包含a[i])的最小和
	min_left[0] = min_until[0];
	for(i = 1;i < n;i++)
	{
		if(a[i] + min_until[i - 1] < a[i])
		{
			min_until[i] = a[i] + min_until[i - 1];
			min = min < min_until[i] ? min : min_until[i];
			min_left[i] = min;
		}
		else
		{
			min_until[i] = a[i];
			min = min < min_until[i] ? min : min_until[i];
			min_left[i] = min;
		}
	}
	max_until[n - 1] = a[n - 1];
	max = max_until[n - 1];
	max_right[n - 1] = max_until[n - 1];
	for(i = n - 2;i >= 0;i--)
	{
		if(a[i] + max_until[i + 1] > max_until[i + 1] && a[i] + max_until[i + 1] > a[i])
		{
			max_until[i] = a[i] + max_until[i + 1];
			max = max > max_until[i] ? max : max_until[i];
			max_right[i] = max;
		}
		else
		{
			max_until[i] = a[i];
			max = max > max_until[i] ? max : max_until[i];
			max_right[i] = max;
		}
	}
	min_until[n - 1] = a[n - 1];
	min = min_until[n - 1];
	min_right[n - 1] = min_until[n - 1];
	for(i = n - 2;i >= 0;i--)
	{
		if(a[i] + min_until[i + 1] < a[i])
		{
			min_until[i] = a[i] + min_until[i + 1];
			min = min < min_until[i] ? min : min_until[i];
			min_right[i] = min;
		}
		else
		{
			min_until[i] = a[i];
			min = min < min_until[i] ? min : min_until[i];
			min_right[i] = min;
		}
	}
	max = myfabs(max_left[0],min_right[1],min_left[0],max_right[1]);
	for(i = 1;i < n - 1;i++)
	{
		max = max > myfabs(max_left[i],min_right[i + 1],min_left[i],max_right[i + 1]) ? max : myfabs(max_left[i],min_right[i + 1],min_left[i],max_right[i + 1]);
	}
	printf("%d\n",max);
	return 0;
}
