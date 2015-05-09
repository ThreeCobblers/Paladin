#变量和基本类型
重点笔记:
###无符号类型
`char类型的具体类型可能是unsigned char或者signed char,具体是哪一个要根据具体编译器决定,所以如果是一个通用性的代码,不要在计算表达式里面使用char类型参与,这样不同编译器跑出来的结果可能不一样.`

###类型转换
*	我们将有符号的变量赋值给无符号变量,如果溢出,有符号的补码会只保留属于无符号那一部分,还是有意义的数.
*	我们将无符号的变量赋值给有符号的变量,如果溢出,那么得到的结果是未定义的,从啥事没有到计算机冒烟都有可能:smile:(GCC 貌似没事)
*	无符号和有符号的变量运算会先转化为无符号的再运算.
*	含有无符号变量的表达式一定要注意,例如unsigned int a = 0; a--; a 又是个正数.

###void *
在C++中void*和C中的void*不太一样,C中允许将void*变量不用转型的赋给任何类型指针变量,而C++中必须显式的转换之后才可以(GCC加上-fpermissive可以过)

	void* ptr = NULL;
	int *a = (int*)ptr; //显式的加上int*转换

###前缀和后缀
C++的整形,浮点型和字符型字面值可以在前/后加前/后缀,相关前缀后缀如下:
字符前缀:
*	u: Unicode 16字符, char16_t
*	U: Unicode 32字符, char32_t
*	L: Unicode 宽字符, wchar_t
*	u8: Unicode UTF-8, char
后缀:
整形后缀
*	u/U: unsigned
*	l/L: long
*	ll/LL: long long
浮点型后缀:
*	f/F: float
*	l/L: long double
例如: 3.14F

###引用和指针
####引用
引用相当于是变量的别名,必须在定义时候就初始化,而且以后不能再更改.
####引用和指针的相似
*	???
####引用和指针的区别
*	指针本身就是一个对象,可以进行赋值和拷贝,可以更改其指向
*	指针不需要在定义时候就赋初值.
*	引用由于这些限制,可操作性要比指针小很多,所以也安全的很多,而且使用起来更简单,不用解引用.

Tip:
	指针由于可以在定义时候不赋初值,这也是造成程序出错的一大隐患,建议指针
	在定义时候就赋初值,比如初值NULL等.

###extern 关键字
extern关键字是表明当前变量是引用外部变量,它用来表示声明一个变量,所以可以是同一个
变量多次声明,但是只能有一次定义,如果在extern声明时候赋初值,那既是声明也是定义.

###const 关键字
const是一个类型限定符,它限制了对应对象的值不能再被改变,关于const关键字有以下几点值得注意:

*	const类型的对象在定义的时候必须初始化
*	默认情况下,const对象只能在本文件内有效,所以可以取代define,可以被到处include, 如果想在其他文件也有效,加上extern.
*	const类型变量不能赋值给非const类型变量,反之可以.

###类型别名
	typedef double *ptr;
ptr就是double指针,这样可能会有一个问题:

	typedef double *ptr;
	const ptr a; 
a是一个指向double的常量指针, 即double *const而不是const double *,这与define ptr double*是不一样的.

###other
观察程序:
	double dval = 3.14;
	int &val = dval;
这样程序会出错,但是const int &val = dval就不会出错,这是因为:把dval赋值给val时候,产生了一个const int的临时变量.
