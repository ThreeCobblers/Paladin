#字符串库函数

##介绍
字符串有很多库函数,很多面试也会考查这些,这些东西大多都是细节题,需要仔细考虑很多边界条件,以写出强壮的代码,在简单的实现了六个cstring的六个库函数之后,大致总结了一下几点需要注意:

*	输入参数是什么类型,该不该是const修饰
*	输入的指针是否为NULL
*	字符串处理完毕后,新产生的字符串末尾是否要加'\0'
*	要不要返回值,该返回什么类型的

还有一些我觉得可能需要考虑的:

*	有没有地址重叠
*	需不需要优化做法

##代码
字符串库函数的实现一般都很简单,如果不考虑性能那么基本都是很naive的算法,只是细节需要注意,相关代码如下:

```C++
//leetcode原题.要考虑溢出,非法字符,开始有空格
int atoi(const char *str){
	int sum = 0;  // 存负值.
	bool isMinus = false;
	const char* p = str;
	if(!p)	return 0;
	while(*p == ' ' && *p != '\0') p++; //空格
	if(*p == '\0')	return 0;
	if(*p == '-'){
		isMinus = true;
		p++;
	}else{
		if(*p == '+') p++;
	}
	while(*p != '\0'){
		int cur = *p++ - '0';
		if(!(cur >= 0 && cur <= 9))	break;  //非法字符
		if(isMinus && sum == INT_MIN/10 && cur > INT_MAX%10 + 1){
			return INT_MIN;
		}
		if(isMinus && sum < INT_MIN/10){
			return INT_MIN;
		}
		if(!isMinus && sum == -INT_MAX/10 && cur > INT_MAX%10){
			return INT_MAX;
		}
		if(!isMinus && sum < -INT_MAX/10){
			return INT_MAX;
		}
		sum = sum*10 - cur;
	}
	if(!isMinus)	return -sum;
	return sum;
}

//考虑输入指针不为空,输入参数使用const char
int strlen(const char *str){
	int len = 0;
	assert(str);  //判断不为NULL
	while(*str++ != '\0'){
		len++;
	}
	return len;
}

// 考虑输入参数的const性,输入参数是否合法,返回值,最后位置为'\0'
// 至于src和dest地址重叠问题,libc里面并没有考虑,我觉得考虑一下还是很好的.
char *strcpy(char *dest,const char *src){
	assert(dest && src);  //输入参数不为NULL
	char* address = dest;
	int lens = strlen(src);
	int lend = strlen(dest);
	if(src + lens > dest){ // 从后往前拷贝
		dest[lens] = '\0';   //当lens < lend就很重要
		for(int i = lens - 1; i >= 0; i--){
			dest[i] = src[i];
		}
	}else{ //从前往后拷贝
		for(int i = 0; i < lens; i++){
			dest[i] = src[i];
		}
		dest[lens] = '\0';  //当lens < lend就很重要
	}
	return address; //注意此函数有返回值
}

//注意事项和strcpy基本相同
char *strncpy(char *dest,const char *src, int n){
	assert(dest && src);
	char *address = dest;
	int lens = strlen(src);
	int lend = strlen(dest);
	if(src + lens > dest && src + n > dest){ // 从后往前拷贝
		dest[min(lens, n)] = '\0';
		for(int i = min(lens, n) - 1; i >= 0; i--){
			dest[i] = src[i];
		}
	}else{ //从前往后拷贝
		for(int i = 0; i < lens && i < n; i++){
			dest[i] = src[i];
		}
		dest[min(lens, n)] = '\0';
	}
	return address;
}

//注意输入参数const性和非NULL性
// KMP
int strstr(const char *haystack, const char *needle){
	assert(haystack && needle);
	int ln = strlen(needle);
	if(ln == 0)	return 0;
	int com[ln], next[ln];
	com[0] = 0;
	int k;
	for(int i = 1; i < ln; i++){
		k = com[i-1];
		while(1){
			if(needle[k] == needle[i]){
				com[i] = k + 1;
				break;
			}else{
				if(k == 0){
					com[i] = 0;
					break;
				}
				k = com[k - 1];
			}
		}
	}
	for(int i = 0; i < ln - 1; i++)
		next[i+1] = com[i];
	next[0] = -1;
	int lh = strlen(haystack);
	int i = 0, j = 0;
	while(i + ln - j < lh + 1){
		if(j == ln)	return i - ln;
		if(haystack[i] == needle[j]){
			i++;
			j++;
		}else{
			if(next[j] == -1){
				i++;
			}else{
				j = next[j];
			}
		}
	}
	return -1;
}

//输入参数const性和非NULL,尾赋'\0', 返回值
char *strcat(char *strDest, const char *strScr){
	assert(strDest && strScr);
	if(!strScr)	return strDest;
	char* p = strDest;
	while(*p){
		p++;
	}
	while(*strScr){
		*p++ = *strScr++;
	}
	*p = '\0';
	return strDest;
}

//输入参数const性和非NULL,
int strcmp(const char *str1,const char *str2){
	assert(str1 && str2);
	//这样写很简洁
	while(*str1 && *str2 && (*str1 == *str2)){
		str1++;
		str2++;
	}
	return (*str1) - (*str2);
}

//注意输入参数是void*和const void*, 输出参数是void*,要保证输出参数非NULL
//libc使用了page copy, unsigned long copy做到快速拷贝
void *memcpy(void *dest, const void *src, size_t count){
	assert(src && dest);
	if(!src || !dest)	return NULL;
	unsigned char *d = (unsigned char*)dest, *s = (unsigned char*)src;
	while(count--){
		*d++ = *s++;
	}
	//不需要设置'\0',因为是内存拷贝
	return dest;
}
```
