/*
在一个整型数组中，仅有一个数字出现了一次，而其他数字都正好出现了三次，请用最快的方法找到出现一次的那个数字
*/
/* 想法：将所有数字用二进制来表示，因为每个数字都出现了三次，所以每一的和应该是3的倍数 + 缺失数字的对应二进制位，要么是0，要么是1
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