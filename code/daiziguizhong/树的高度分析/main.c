/*
树的高度分析
有一个棵树，不一定是二叉树，有n个节点，编号为0到n-1。有一个数组A，数组的索引为0到n-1，
数组的值A[i]表示节点i的父节点的id，根节点的父节点id为-1。给定数组A，求得树的高度。 
分析这个题目我们首先把数组写出来，然后进一步分析，就很明了了，如下例子： 333-1201234
*/
#include <stdio.h>

#define N 20
int b[N];//用来保存中间计算结果，避免重复计算
int heighOfTree(int a[],int i); 
int main()
{
	int a[N];
	int i,n,max = -1;
	memset(b,0,sizeof(b));
	scanf("%d",&n);
	for(i = 0;i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i = 0;i < n;i++)
	{
		max = max > heighOfTree(a,i) ? max : heighOfTree(a,i);
	}
	printf("%d\n",max);
	return 0;
}
//递归，知道遇到根节点-1，或者已经计算过的节点
int heighOfTree(int a[],int i)
{
	if(a[i] == -1)
	{
		return 1;
	}
	else if(b[i])
	{
		return b[i];
	}
	else
	{
		b[i] = 1 + heighOfTree(a,a[i]);
		return b[i];
	}
}