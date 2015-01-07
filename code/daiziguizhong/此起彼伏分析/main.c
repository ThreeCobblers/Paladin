/*
有这样一个数组A，大小为n，相邻元素差的绝对值都是1.如： A={4,5,6,5,6,7,8,9,10,9}。 
现在，给定A和目标整数t，请找到t在A中的位置。除了依次遍历，还有更好的方法么
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
