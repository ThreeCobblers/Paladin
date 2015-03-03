#字符串,向量和数组
##命名空间
###定义命名空间
```C++
namespace Hu{
	int a;
}
```
###使用命名空间
*	using namespace Hu;
*	using Hu::a;
*	Hu::a;

在头文件中使用推荐使用第三种,因为头文件会被很多cpp文件包含,若使用前两个可能会有命名问题(例如某个cpp文件也定义了一个变量a)

###string对象
string类提供很多方法和友元函数,需要知道的有:

成员函数:

*	begin/end/rbegin/rend
*	size/length/max_size/resize/capacity/reserve/empty/clear
*	[]/at
*	+=/append/push_back/
*	assign/insert/erase/swap/copy
*	c_str/find/substr/compare

友元函数:

*	getline
*	<</>>/==/!=/</>

Note:	string::size_type 是无符号数,要注意
Note:	#include<cctype>文件中有isalpha, isdigit, isalnum等函数.

###string源码剖析

###vector
vector类模板不能盛放引用,引文它不是对象,同样也没有引用的数组.
####常用成员函数
*	begin/end/rbegin/rend
*	size/max_size/capacity/resize/reserve/empty/clear
*	[]/at/front/back
*	append/push_back/pop_back/insert/erase/swap

可以看到和string的成员函数很像.
###数组
begin/end全局函数可以获取数组的首尾迭代器.
