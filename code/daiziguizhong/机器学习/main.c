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
		R = RAND_MAX - RAND_MAX % N; //ȥ��β��,��֤�ȸ���
		count = 0;
		
		for(i = 0;i < n;i++)
		{
			k = rand();
			while(k > R)
			{
				k = rand();//ֱ����������ȸ��ʵ�����
			}
			k = k % N;
			//��pΪ0.03Ϊ������k��ֵΪ0,1,2ʱ���������Ϸ���
			if(k < p_int)//�������
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
	R = RAND_MAX - RAND_MAX % N; //ȥ��β��,��֤�ȸ���
	for(i = 100;i <= 10000;i += 100)
	{
		count = 0;
		
		for(j = 0;j < i;j++)
		{
			k = rand();
			while(k > R)
			{
				k = rand();//ֱ����������ȸ��ʵ�����
			}
			k = k % N;
			//��pΪ0.03Ϊ������k��ֵΪ0,1,2ʱ���������Ϸ���
			if(k < p_int)//�������
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