/*
输入大写字母的偏序关系
输出满足该偏序关系的拓扑序列
列如：

输入
AB
AC
输出
ABC
ACB
*/
#include <stdio.h>
#define MAX_VERTEX_NUM 20
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode{
	int info;
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct
{
	AdjList vertices;
	int vexnum;
	int arcnum;
}ALGraph;
int mapabc[MAX_VERTEX_NUM],indegree[MAX_VERTEX_NUM],visit[MAX_VERTEX_NUM];
char output[MAX_VERTEX_NUM];

int CreateAL(ALGraph *G);
int map(char c);
int TopologicalSort(ALGraph *G);
void DFS(ALGraph *G,int n);
char find(int i);

int main()
{
	ALGraph *G = (ALGraph *)malloc(sizeof(ALGraph));
	memset(G,0,sizeof(ALGraph));
	memset(mapabc,-1,sizeof(mapabc));
	memset(indegree,0,sizeof(indegree));
	memset(visit,0,sizeof(visit));
	CreateAL(G);
	//TopologicalSort(G);
	DFS(G,0);
	return 0;
}
int CreateAL(ALGraph *G)
{
	int i;
	char before,after;
	ArcNode *p = NULL,*q;
	scanf("%d %d",&(G->vexnum),&(G->arcnum));
	getchar();
	for(i = 0;i < G->arcnum;i++)
	{
		scanf("%c%c",&before,&after);
		getchar();
		
		q = G->vertices[map(before)].firstarc;
		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = map(after);
		p->nextarc = q;
		G->vertices[map(before)].firstarc = p;
		
		indegree[map(after)]++;
	}
	return 0;
}
int map(char c)
{
	int i = 0,j = 0;
	if(mapabc[c - 'A'] != -1)
	{
		return mapabc[c - 'A'];
	}
	for(i = 0;i < MAX_VERTEX_NUM;i++)
	{
		if(mapabc[i] != -1)
		{
			j++;
		}
	}
	mapabc[c - 'A'] = j;
	return j;
}
char find(int i)
{
	int j = 0;
	for(j = 0;j < MAX_VERTEX_NUM;j++)
	{
		if(mapabc[j] == i)
		{
			return (char)('A' + j);
		}
	}
	return 0;
}
//求一个拓扑序列
int TopologicalSort(ALGraph *G)
{
	int S[MAX_VERTEX_NUM * 2];
	int top = 0,k,count,i;
	ArcNode *p = NULL;
	for(i = 0;i < G->vexnum;i++)
	{
		if(!indegree[i])
		{
			S[top] = i;
			top++;
		}
	}
	count = 0;
	while(top != 0)
	{
		top--;
		i = S[top];
		printf("%c",find(i));
		count++;
		for(p = (G->vertices[i]).firstarc; p ;p = p->nextarc)
		{
			k = p->adjvex;
			if(!(--indegree[k]))
			{
				S[top] = k;
				top++;
			}
		}
	}
	if(count < G->vexnum)
		return -1;
	else
		return 0;
}
//求所有拓扑序列
void DFS(ALGraph *G,int n)
{
	int i;
	ArcNode *p = NULL;
    if(n == G->vexnum)
	{
		for(i = 0;i < G->vexnum;i++)
		{
			printf("%c ",output[i]);
		}
		printf("\n");
		return;
	}
	for(i = 0;i < G->vexnum;i++)
	{
		if(!indegree[i] && !visit[i])
		{
			visit[i] = 1;
			output[n] = find(i);
			for(p = (G->vertices[i]).firstarc;p;p = p->nextarc)
			{
				indegree[p->adjvex]--;
			}
			DFS(G,++n);
			n--;
			visit[i] = 0;
			for(p = (G->vertices[i]).firstarc;p;p = p->nextarc)
			{
				indegree[p->adjvex]++;
			}
		}
	}
}