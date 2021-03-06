#函数
##函数基础
*	函数实参求值顺序没有规定,所以像`f(i, i++)`这样的,两个参数的求值顺序没有要求,所以结果全凭编译器.
*	函数形参可以没有名字,比如一些函数模板常用这样的技术来确定类型
*	函数返回值不能是数组或者函数类型,不过可以是数组指针和函数指针
*	函数局部非静态变量的定义,如果该类型不含默认初始化,则是未初始化状态
*	函数局部静态变量会被初始化
*	如果一个函数永远也不会被用到,那么可以只有声明没有定义
*	数组作为形参其实会退化为指针,为了确定数组的大小,可以采用三种方法:
	*	数组中自带特殊值,例如字符串中的'\0'
	*	传入数组的begin和end指针(迭代器),可以用库函数begin和end获取
	*	传入数组时候再传入表示数组大小的变量.
*	传递多维数组时候,除了第一维度可以不指定,其他维度必须要指定

##返回值
*	函数返回值一般都是右值,但是如果返回的是引用则可以为左值
*	函数返回数组指针: `int (*func()) [10]`注意维度大小必须指定

##函数重载
*	main函数不能被重载
*	函数重载要求形参数目或者类型不一样
*	顶层const不能作为函数重载的区别,比如`void f(const int)`和`void f(int)`
*	const引用或者指针(底层const)可以作为重载函数的区别,比如`void f(const int&)`和`void f(int&)`,此时如果遇到的参数是const int类型自然调用第一个,而如果是int类型则优先调用第二个.
*	如果我们在内层作用域声明名字,那么它将屏蔽外层作用域声明的同名实体.
```C++
void print(double);
int main(){
	void print(string);
	print(2); //出错,因为内层屏蔽了外层
}
```
C++名字查找在类型检查之前,所以会先找到内层的这个,不管它类型是否匹配.

##默认实参
函数某个参数设置默认参数后,其右边的参数必须都拥有默认参数.另外,不能通过默认参数不同来实现函数重载.

##内联函数
内联函数只是对编译器的请求,至于实际上内不内联,还是编译器说的算,内联函数一般直接把其定义写在头文件中.

##assert和NDEBUG
编译时候打开NDEBUG宏,代码中assert语句将失效.

##常用调试名
|符号|意义|
|:----:|:----:|
|`__func__`|函数名|
|`__FILE__`|文件名|
|`__LINE__`|行号|
|`__TIME__`|编译时间|
|`__DATE__`|编译日期|

##函数匹配
C++中由于函数可以重载,所以在发生函数调用时候,编译器会去选择使用哪一个函数,选择的规则是先寻找最佳匹配,如果没有最佳匹配说明有二义性,则会报错.为了实现最佳匹配,实参类型会发生转换,转化的等级有五种:

*	精确匹配:类型完全一样,或者是数组名与指针,函数名与函数指针这样的.
*	通过const转换实现匹配
*	通过类型提升实现匹配,例如char提升到int
*	通过算术类型转换,例如double转为int
*	通过类类型转换实现匹配

##函数指针
*	函数指针的声明如下:`bool (*f)(string, string)`,声明的函数变量等同于函数指针,例如函数声明`bool compare(string, string);`里compare也是函数指针,它可以直接赋值给f,`f=compare`,当然也可以`f=&compare`,这两个是一样的.
*	函数指针不存在转换.
*	重载函数的指针类型必须要和某个重载函数完全匹配.
*	函数指针可以作为形参,用法和一般的定义函数指针变量一样.
*	函数指针也可以作为返回值,例如`int (*func()) ()`





