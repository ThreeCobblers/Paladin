
/*���������⣺�������ִ�

�������ִ��������ڵ绰���뷭�룺��һ�����ִ�������12259��ӳ�䵽��ĸ���飬���磬1 -> a�� 2-> b��... �� 12 -> l ��... 26-> z��
��ô��12259 -> lyi �� abbei �� lbei �� abyi������һ�����ִ����ж��Ƿ���ת�����ַ���������ܣ����ӡ�����п��ܵ�ת���ɵ��ַ���

����ܼ򵥣��õݹ���Ժ��������ɽ⣬������Ӷ���Ŀռ䣬�����м���������ܸ���Щ
����ֱ��ʹ�ö��飬������Ҫ���ɽ����������ѡ��ݹ�
*/
#include <stdio.h>

#define N 40
char a[N];
int n;
char map[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n', \
			'o','p','q','r','s','t','u','v','w','x','y','z'};

void trans(char num_string[],int e,int i);
int main()
{
	int i;
	char num_string[N];
	
	scanf("%s",num_string);
	n = strlen(num_string);

	trans(num_string,0,0);
	return 0;
}
void trans(char num_string[],int e,int i)
{
	char c[3] = {'\0','\0','\0'};
	if(i >= n)
	{
		printf("%s\n",a);
		return;
	}
	if(num_string[i] - '1' < 0)
	{
		return;
	}
	if(i == n - 1)
	{
		a[e] = map[num_string[i] - '1'];
		printf("%s\n",a);
		a[e] = '\0';
		return;
	}
	
	a[e] = map[num_string[i] - '1'];
	trans(num_string,e + 1,i + 1);
	a[e] = '\0';

	c[0] = num_string[i];
	c[1] = num_string[i + 1];
	if(atoi(c) >= 26)
	{
		return;
	}
	a[e] = map[atoi(c) - 1];
	trans(num_string,e + 1,i + 2);
	a[e] = '\0';
	return ;
}