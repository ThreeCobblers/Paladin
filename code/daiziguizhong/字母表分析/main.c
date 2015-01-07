#include <stdio.h>

#define N 20
#define M 20
#define S 26

int TopologicalSort(int a[][S]);
int find(int a[]);
int dfs(int a[][S],int n,int i);
int inversefine(int j,int a[]);
int visit[S],t,topo[S];

int main()
{
	int a[S][S];
	int i,n = 0;
	int map[S];

	char b[M][N];
	char *p,*q;

	FILE *fp = NULL;

	fp = fopen("in.txt","r");
	while(fscanf(fp,"%s",&b[n]) != EOF)
	{
		n++;
	}
	fclose(fp);
	
	memset(visit,0,sizeof(visit));
	memset(a,0,sizeof(a));
	memset(map,-1,sizeof(map));
	for(i = 0; i < n - 1;i++)
	{
		p = b[i];
		q = b[i + 1];
		while(*p == *q)
		{
			p++;
			q++;
		}
		if(*p && *q)
		{
			map[*p - 'A'] = map[*p - 'A'] == -1 ? find(map) : map[*p - 'A'];
			map[*q - 'A'] = map[*q - 'A'] == -1 ? find(map) : map[*q - 'A'];
			a[map[*p - 'A']][map[*q - 'A']] = 1;
		}
	}
	n = 0;
	while(map[n] != -1) 
	{
		n++;
	}
	if(TopologicalSort(a,n))
	{
		for(i = 0;i < n;i++)
		{
			printf("%c  ",inversefine(topo[i],map) + 'A');
		}
		printf("\n");
	}
	else
	{
		printf("No Solution!");
	}
	return 0;
}
int inversefine(int j,int a[])
{
	int i = 0;
	while(a[i] != j) i++;
	return i;
}
int find(int a[])
{
	int i = 0,j = 0;
	for(i = 0;i < S;i++)
	{
		if(a[i] != -1)
		{
			j++;
		}
	}
	return j;
}
int TopologicalSort(int a[][S],int n) 
{
	int i = 0;
	t = n;
	for(i = 0;i < n;i++)
	{
		if(!visit[i])
		{
			if(!dfs(a,n,i))
				return 0;
		}
	}
    return 1;
}
int dfs(int a[][S],int n,int i)
{
	int j;
	visit[i] = -1;
	for(j = 0;j < n;j++)
	{
		if(a[i][j])
		{
			if(visit[j] < 0)
				return 0;
			else if(!visit[j] && !dfs(a,n,j))
				return 0;
		}
	}
	visit[i] = 1;
	topo[--t] = i;
	return 1;
}