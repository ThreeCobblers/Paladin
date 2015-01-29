#字符串匹配问题
:smirk:

对于字符串匹配问题,关键点都实在与对'*'号的处理.当'*'号出现时,我们需要标注出'*'的存在性,然后修改字符串的定位.

##依赖于前一字符的'*'
在这个问题中,'*'号的意义依赖于其前导字符,表示前导字符的任意次存在性.

###递归法
在递归法中,我们对于isMatch(i,j)的理解为以i开头和以j开头的字符串的匹配情况.
每当发现当前字符的下一个字符为'*'时,就需要递归的判断当前字符被使用了0次或N次的情况.
时间复杂度为O(n * m!) ?

```c++
bool valid(const char c,const char s){
	return (c==s)||(s=='.');
}
bool isMatch(const char*s,const char*p){
	if(*s == '\0'){
		while(*p == '*')
			p++;
		return *p == '\0';
	}
	if(*p == '\0')
		return *s == '\0';

	if(valid(*s,*p)){
		return isMatch(s+1,p+1);
	}else if(*p == '*'){
		return (isMatch(s,p+1) || (valid(*s,*(p-1)) && isMatch(s+1,p)));
	}else 
		return false;
}
```

###迭代法
详见下面的迭代法.

###DP
详见下面的DP

##不依赖前导字符的'*'
在这种情况下,'*'有了极大的自由度.不过处理起来的思路还是与前面讨论的情况十分的类似

###递归法
与前一种情况类似,直接给代码 :smirk:

```c++
/*
 * Recurssion
 * Time complexity : O(m * n!) or O(m! * n!) ?
 */
bool isMatch_recurr(const char* s,const char *p){
	if(*s=='\0'){
		while(*p == '*')
			p++;
		return *p=='\0';
	}

	if(*p=='\0')
		return *s=='\0';

	if(*p == *s || *p == '?')
		return isMatch_recurr(s+1,p+1);

	if(*p == '*'){
		while(*p == '*')
			p++;;//p向前移动,跳过重复的*
		if(*p == '\0')
			return true;
		else{
			while(*s && !isMatch_recurr(s,p))
				s++;//s向前移动,跳过不相等的项
			return *s!='\0';//如果*s=='\0', 代表走到最后都没有匹配
		}
	}
	return false;
}
```

###迭代法
在迭代法中,因为当前'*'的极大的匹配能力,我们可以在每次遇到'*'时,都将先前的字符认为是处于已经被匹配了的状态.

```c++
/*
 * Iteration time O(n*m)
 * 标记先前的位置,为之后失败时的回溯提供条件
 * 注意: p串中每次在遇到*号时,都可以前移的原因时*的极大的匹配能力 :)
 */

bool isMatch(const char*s, const char* p){
	bool hasStar = false;
	char *sptr = s;
	char *pptr = p;
	for(;sptr!='\0';sptr++,pptr++){
		if(*pptr == '?' || *pptr==*sptr){
			;
		}else if(*pptr == '*'){
			hasStar = true;
			s = sptr;
			p = pptr;
			while(*p == '*')
				p++;
			if(*p == '\0')
				return true;
			pptr = p - 1;
			sptr = s - 1;
		}else{
			if(!hasStar)
				return false;
			s++;
			pptr = p-1;
			sptr = s-1;
		}
	}

	while(*pptr == '*')
		pptr++;
	return *pptr=='\0';
}
```
###DP
我们在使用递归或者迭代的方法处理匹配问题时,考虑的角度时[i->end][j->end]的匹配情况.
通过观察递归的解法,不难发现其中存在有子问题的重叠.考虑使用DP.
在DP中,考虑的角度时[1->i][1->j]的匹配情况.(最终的匹配情况为[end][end])
子问题重叠:
无后效性:
```c++
	if p[j-1]=='*'
		for(i = 1 -> len)
			dp[i][j] = dp[i][j-1];
	else 
		for(i = 1 -> len)
			dp[i][j] == dp[i-1][j-1]
```
