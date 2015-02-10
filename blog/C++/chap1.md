#第一章: 编写一个简单的C++程序

这一章,很简单,大多都是科普性质的内容,我就说一下里面有几个东西可以注意一下的吧.

##cout和cin
这两个分别是ostream和istream的对象,有缓冲区,只有遇到endl,或者程序终端或者输入输出错误等原因会刷新缓冲区.

另外,对于cin输出流,如何判定读取数据结束了,即文件结束符是什么? 在UNIX是Ctrl+D

##cerr和clog
cin和cout我们已经用了很多了,但是貌似对cerr和clog不是很熟悉,cerr和clog和cout一样都是ostream类型对象,用来输出程序的警告和错误信息,使用方法和cout几乎一样,和cout不同的是cerr和clog的输出是输出到标准错误流,cout输出到标准输出流,而且cerr是无缓冲区直接刷新的,clog是有缓冲区的(默认情况下).

例如如下程序:
```C++
#include <iostream>

using namespace std;

int main(){
	int a = 2;
	cout<<a;
	clog<<"log";
	sleep(4);
	cerr<<"err";
	cerr<<endl<<"error"<<endl;
}
```
直接执行:`./a.out`

发现输出是log2err等,可知cout是用缓冲的,而cerr是无缓冲的.

然后执行:`./a.out > out 2> err`

就会发现:out文件里面是2, err文件里面是logerr等(标准错误流)


