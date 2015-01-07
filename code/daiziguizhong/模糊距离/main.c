/*
模糊距离分析

原题

X和Y都是只有0和1组成的字符串。D(X,Y)称为模糊距离，定义如下： 首先删除X和Y从头开始的公共子串 然后将X和Y剩
下部分的长度相加得到模糊距离 例如D(1000,1111)，首先，删除子串“1”，然后剩下“000”和“111”长度都是3，相
加为6，则 D(1000,1111)=6。 例如D(101,1100)，首先删除公共子串“1”，然后剩下"01"和"100"长度分别为2，3，相加
为5，则 D(101,1100)=5
*/
#include <stdio.h>
#include <assert.h>

#define MAXLEN 30
#define N 30
#define ZERO(T) (T)->c = '0',(T)->depth = 1,(T)->father = NULL,(T)-> lchild = NULL,(T)->rchild = NULL

typedef struct Node
{
	char c;
	int depth;
	struct Node *father;
	struct Node *lchild;
	struct Node *rchild;
} *TireNode;

void creat_tire_tree(TireNode r,char start_0[][MAXLEN + 1],char startof_1[][MAXLEN + 1],int n1,int n2);
int max_disoffuzzy(TireNode r);

int main()
{
	int i,n,n1,n2;
	char a[N][MAXLEN + 1];
	char startof_0[N][MAXLEN + 1];
	char startof_1[N][MAXLEN + 1];

	TireNode r = (TireNode)calloc(1,sizeof(TireNode));
	ZERO(r);

	scanf("%d",&n);
	assert(n <= N);

	for(i = 0;i < n;i++)
	{
		scanf("%s",a[i]);
	}

	creat_tire_tree(r,startof_0,startof_1,n1,n2);
	printf("%d\n",max_disoffuzzy(r));
	return 0;
}
void creat_tire_tree(TireNode r,char startof_0[][MAXLEN + 1],char startof_1[][MAXLEN + 1],int n1,int n2)
{

}
int max_disoffuzzy(TireNode r)
{
	return 0;
}