/*
�����ַ�������������Ƿ�ƥ�䣬���磬
1. "()" yes��

2. ")(" no��

3. "(abcd(e)" no��

4. "(a)(b)" yes��
Ҫ������õݹ�д������ʵ�ֲ����Գ���һ��ѭ����䡣
*/
#include <stdio.h>
#define N 20
int bm(char *p);
int main()
{
	char s[N];
	scanf("%s",s);
	printf("%s\n",bm(s) == 0 ? "yes" : "no");
	system("pause");
	return 0;
}
int bm(char *p)
{
	if(p[0] == '\0')
	{
		return 0;
	}
	switch(p[0])
	{
	case '(':
		return 1 + bm(p + 1);
		break;
	case ')':
		return bm(p + 1) - 1;
		break;
	default:
		return bm(p + 1);
	}
}