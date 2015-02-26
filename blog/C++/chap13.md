#拷贝控制
拷贝控制包含构造函数,析构函数,拷贝构造函数,赋值运算符,移动拷贝构造函数和移动赋值运算符这五种,其中最后两种为C++11新标准.虽然我们不管这些函数时候,C++编译器也会为我们生成一个默认的相应函数,但是有时候使用默认的函数是不行的,需要我们手动的去实现.另外,如果我们手动实现了某个函数,那么编译器就不会再为它生成相应的默认函数.

##拷贝构造函数
*	拷贝构造函数形式如:`A(const A& rhs){...}`,通常不是explicit的.
*	拷贝构造函数调用场合:
	*	声明并初始化对象时候:`A a1(a2);  A a1 = a2;`
	*	将一个对象作为实参传递给非引用形参
```C++
class A{
	public:
		A(int i){}
};

void func(A a){

}

A a;
func(a);
```
	*	函数返回类型为一个非引用类型对象
*	有些时候编译器会绕过拷贝构造函数,例如:
```C++
class A{
	public:
		A(int i){}
};

//实际上应该是先将2提升为A,再拷贝构造,
//但是编译器优化为A a(2),直接初始化构造
A a = 2;
```
##赋值运算符
我们有时候需要重载赋值运算符来实现像操作内置类型那样操作我们自定义的类.

*	赋值运算符函数一般形式:`A& operator=(const A& rhs){...}`

##析构函数
*	析构函数一般形式:`~A(){ ... }`
*	析构函数不能有参数,所以是不能被重载的.
*	析构函数先执行函数体,然后再执行成员变量的销毁工作,销毁的顺序与构造的顺序相反.
*	调用析构函数的场合:
	*	对象变量离开其作用域被销毁时候
	*	一个对象被销毁,其成员对象也会被销毁
	*	容器被销毁时候,其盛放的元素也会被销毁
	*	动态分配的对象被delete时候
	*	临时对象生命期结束时候

##两个原则
*	在需要自定义析构函数时候,一般也要自定义拷贝构造函数和赋值运算符
*	在需要自定义拷贝构造函数时候,一般也要自定义赋值运算符

##阻止拷贝
*	我们以前的做法是将拷贝构造函数和赋值运算符函数设为私有函数
*	新标准提供了= delete函数修饰符,可以在拷贝构造函数和赋值运算符加上= delete即可禁止其被调用

>拷贝构造函数和赋值运算符等该如何实现还要考虑到类的特点,类可以像值一样,一旦拷贝,两个对象的资源无关,也可以像指针一样,拷贝之后还是关联到同一个资源.

##行为像值的类
行为像值的类在拷贝的过程中需要深拷贝,即拷贝其整个资源,而不是简单的指针或者引用.我们举个例子来看一下:
```C++
class A{
	public:
		A(int sz = 1) : resource(new int[sz]), n(sz){} 

		~A(){
			delete [] resource;
		}
		//拷贝构造函数
		A(const A& rhs){
			n = rhs.n;
			resource = new int[n];
			uninitialized_copy(rhs.resource, rhs.resource + n, resource);
		}
		//赋值运算符
		//这样写的目的是因为new的时候可能会有异常
		//所以先拷贝构造一个tmp,再swap
		A& operator=(const A& rhs){
			A tmp = rhs;
			swap(*this, tmp);
			return *this;
		}

		void swap(A &lhs, A& rhs){
			using std::swap;
			swap(lhs.n, rhs.n);
			swap(lhs.resource, rhs.resource);
		}
	private:
		int * resource;
		int n;
};
```
上面代码部分的赋值运算符的实现方法值得注意,这样写的目的以防先删除原资源后,再new却失败了,那么原对象的资源也没有了,就无法恢复了;另外,赋值时候可能rhs就是*this,这种写法也能处理这种情况,拷贝运算符的一般写法还可以这样:
```C++
		A& operator=(const A& rhs){
			if(rhs != *this){
				int *tmp = new int[rhs.n];
				uninitialized_copy(rhs.resource, rhs.resource + n, tmp);
				delete [] resource;
				resource = tmp;
				n = rhs.n;
			}
			return *this;
		}
```

另外上面的代码还有一处需要注意:using std::swap并不表明,下面的那个swap一定是std::swap,只是使得std::swap可见,可以作为候选,如果作用域中还有其他的swap,则根据最佳匹配原则进行匹配(如果resource指向的是一个复杂的类对象,并且此对象有自己的swap函数,那么swap(lhs.resource, rhs.resource)就是调用其成员swap函数而不是std::swap函数)

##行为像指针的类
像shared_ptr这种类行为就像指针,它的实现需要引用记数来辅助.这个记数要实现被多个对象共享(不是所有对象共享,那是static变量),那只能把这个记数变量用动态内存来存储.下面举一个例子:
```C++
class B{
	public:
		B() : resource(new string), count(new int(1)){}
		
		~B(){
			(*count)--;
			if(*count == 0)	delete resource;
		}

		B(const B& rhs){
			resource = rhs.resource;
			count = rhs.count;
			(*count)++;
		}

		B& operator=(const B& rhs){
			B tmp = rhs;
			swap(*this, tmp);
			return *this;
		}

		void swap(B &lhs, B& rhs){
			using std::swap;
			swap(lhs.resource, rhs.resource);
			swap(lhs.count, rhs.count);
		}

	private:
		string * resource;
		int * count;
};
```
上面代码采用了count来记数,可以看到赋值运算符的实现和上面的如出一辙,这样写很简洁,也能规避很多风险.


##对象移动
移动构造函数和移动赋值运算符是C++11新标准里面的...
