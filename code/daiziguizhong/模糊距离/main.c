/*
ģ���������

ԭ��

X��Y����ֻ��0��1��ɵ��ַ�����D(X,Y)��Ϊģ�����룬�������£� ����ɾ��X��Y��ͷ��ʼ�Ĺ����Ӵ� Ȼ��X��Yʣ
�²��ֵĳ�����ӵõ�ģ������ ����D(1000,1111)�����ȣ�ɾ���Ӵ���1����Ȼ��ʣ�¡�000���͡�111�����ȶ���3����
��Ϊ6���� D(1000,1111)=6�� ����D(101,1100)������ɾ�������Ӵ���1����Ȼ��ʣ��"01"��"100"���ȷֱ�Ϊ2��3�����
Ϊ5���� D(101,1100)=5
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