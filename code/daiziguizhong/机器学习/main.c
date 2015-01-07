#include <stdio.h>
#include <stdlib.h>
#define N 100
int main1()
{
	int i,j,n,k,R,count,p_int;
	float p,np;
	FILE *fp;

	/*
	while(scanf("%d %f",&n,&p),n != 0)
	{		
		p_int = (int)(p * N);
		R = RAND_MAX - RAND_MAX % N; //去除尾数,保证等概率
		count = 0;
		
		for(i = 0;i < n;i++)
		{
			k = rand();
			while(k > R)
			{
				k = rand();//直到落在满足等概率的区间
			}
			k = k % N;
			//以p为0.03为例，当k的值为0,1,2时，正面向上发生
			if(k < p_int)//计算次数
			{
				count++;
			}
		}
		printf("%d\n",count);
	}
	*/
	scanf("%f",&p);
	fp = fopen("C:\\Users\\wuxin_bit\\Desktop\\machine.txt","w");
	fclose(fp);
	p_int = (int)(p * N);
	R = RAND_MAX - RAND_MAX % N; //去除尾数,保证等概率
	for(i = 100;i <= 10000;i += 100)
	{
		count = 0;
		
		for(j = 0;j < i;j++)
		{
			k = rand();
			while(k > R)
			{
				k = rand();//直到落在满足等概率的区间
			}
			k = k % N;
			//以p为0.03为例，当k的值为0,1,2时，正面向上发生
			if(k < p_int)//计算次数
			{
				count++;
			}
		}
		np = (count * 1.0) / (i * 1.0);
		fprintf(fp,"%d %.5f\n",i,np);
	}
	fclose(fp);
	return 0;
}