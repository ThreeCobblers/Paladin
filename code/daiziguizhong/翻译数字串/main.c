
/*今日面试题：翻译数字串

翻译数字串，类似于电话号码翻译：给一个数字串，比如12259，映射到字母数组，比如，1 -> a， 2-> b，... ， 12 -> l ，... 26-> z。
那么，12259 -> lyi 或 abbei 或 lbei 或 abyi。输入一个数字串，判断是否能转换成字符串，如果能，则打印所以有可能的转换成的字符串

此题很简单，用递归可以很容易生成解，如果增加额外的空间，保存中间计算结果，能更快些
或者直接使用动归，不过需要生成解向量，因此选择递归
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