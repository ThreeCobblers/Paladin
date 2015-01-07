/*�����Զ
ԭ��
����һ�����飬���ǿ����ҵ��������ཻ�ġ�������������������A��B��A�е����ֺ�Ϊsum(A), B�е�Ԫ�غ�Ϊsum(B)��
�ҵ�������A��B������sum(A) - sum(B)�ľ���ֵ�����ġ� ���磺[2, -1 -2, 1, -4, 2, 8]����ΪA=[-1, -2, 1, -4]
B=[2, 8] ����ֵΪ16
�������⣬��һ�о�����iΪ�ֽ�㣬�ֱ�������������Сֵ��Ȼ������󣬺ͳ���ʦ��˼·����һ��
*/

/*
�Լ��Ĵ���ȱ�ݣ��ظ�����̫�࣬�пձ����ع�
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
	//���� max_left[i]��ʾa[0,i]����������������
	//max_right[i]��ʾa[i,n - 1]����������������
	int a[N],max_left[N],min_left[N],max_right[N],min_right[N];
	int max,max_until[N],min,min_until[N];
	scanf("%d",&n);
	for(i = 0; i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	max_until[0] = a[0];
	max = max_until[0];//max_until��ʾ����a[0,i]�Ұ���a[i](����a[i,n - 1]�Ұ���a[i])������
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
	min = min_until[0];//min_until��ʾ����a[0,i]�Ұ���a[i](����a[i,n - 1]�Ұ���a[i])����С��
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
