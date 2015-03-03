#类
##this指针
C++中每个成员函数都会在形参中隐藏着一个this指针,举个例子说明一下:

```C++
class A{
	public:
		void func(){
			return value;
		}
	private:
		int value;
};

A a;
a.func();
```
实际上是这样的:

```C++
class A{
	public:
		void func(A *const  this){
			return this->value;
		}
	private:
		int value;
};

A a;
A::func(&a);
```
可以看到,调用成员函数时候会传入对象的指针,而成员函数接受A *const的this指针,这个this变量的指向是不能改的,但是指向的对象可以更改.

##const类型成员函数
上面知道了每个成员函数都隐式的传入一个A *const类型的this指针,而const类型成员函数其实很简单,就是用来修改this指针的,使得this指针变为const A *const类型,这样不仅this指针不能改变指向,也不能改变指向的对象值.所以在const成员函数中除了mutable变量外,不允许修改任何成员变量.

常量的对象也只能调用常量函数,因为A::func(&a),如果a是const A,那么传入的必然是const A *const类型的this指针,所以只有常量函数可以接.

##构造函数
*	构造函数不能是const的.
*	默认构造函数: 如果不自己写构造函数,编译器会生成默认构造函数,但是一旦写了,编译器将不再生成默认构造函数.
*	构造函数的初始化成员列表: 只有当初始化成员列表的次序和成员变量在类中的次序一样时候,才能肯定成员变量是按该顺序初始化的,否则初始化的顺序是未定义的.
*	引用或者const变量必须在构造函数初始化成员列表中初始化.
	
	例如:
```C++
class A{
	public:
		A(int x): j(x), i(j){}
	
	private:
		int i;
		int j;
};
```
i,j的初始化顺序就是未定义的,如果是先初始化i那就出问题了.

##隐式类型转换
如果一个类的构造函数只有一个参数,或者刨除有默认参数的外只剩一个参数的,该参数类型可以隐式转化为该类的一个对象:
```C++
class A{
	public:
		A(string str) : value(str){}
	private:
		string value;
}

string str = "hell";
A a = str; // 发生了隐式类型转换
```
要想屏蔽这种转换可以在构造函数前加上explicit关键字,不过显示的构造是没事的.
```C++
class A{
	public:
		explicit A(string str) : value(str){}
	private:
		string value;
}

string str = "hell";
A a = str; // 发生错误
A b(str);  // 显示构造没有问题
```

##struct和class的区别
C++中两者除了默认的访问权限不同以外,其他的一模一样,struct默认的访问权限是public,而class是private.

##友元
友元声明后的函数或者类,可以随意的访问本类的任何变量.

友元函数:`friend void func();`

友元类:`friend class B;`

友元成员函数:`friend void B::func();`

另外,友元声明并不等于函数的声明,如果有需要使用友元函数/类,还需要真正的函数/类声明才行.

```C++
class A{
	public:
		A();
	friend void func();
};

void func();//实际声明

A::A(){
	func();
}
```

友元不具有传递性.

##封装的好处
*	能够保证用户不会无意间破坏类的对象的状态(比如某些成员变量的值)
*	封装成接口后,用户只需要方便的使用接口即可,不必理会实现细节,类的设计者也可以自由的修改函数的实现,不用担心与用户代码的不兼容的问题.

##类内定义类型
我们经常看到在类内通过typedef定义新的类型别名,这样做的好处一个是使得类型的用途更加直观,比如像std::vector里面的size_type类型别名,一看你就能明白它的意思;而是隐藏实现细节,使得你不晓得size_type到底是什么具体类型,是int还是unsigned int?

另外,需要注意的就是:如果类中已有使用外层作用域定义的类型别名,那么在使用之后不能再次定义该类型别名.

```C++
typedef double Money;
class A{
	public:
		Money A(){}
	privaye:
		typedef int Money; // 错误,重新定义
};
```

##内联成员函数
在类内实现的成员函数默认是inline的(实际会不会还看编译器选择),如果不在类内实现的,可以声明出加上inline关键字实现内联.

##mutable关键字
为了使得const成员函数能够修改某些成员变量又不违反const性,可以把这些成员变量声明为mutable.

##返回*this的成员函数
返回*this的成员函数一般的返回值类型是const A&, 用来连续实现函数.比如A.f().g()这样的.如果返回值类型是const A,那么就是原对象的拷贝.

另外,const成员函数返回*this指针肯定要求是const类型的返回值,因为此时this指针的类型是const A *const,所以*this就是const A,所以不能将const A赋值给A类型.

##基于const的重载
C++中成员函数重载可以通过是否为const类型成员函数实现.其实,你可能觉得很奇怪,但是其实原因很简单,因为这个const是修饰this指针的,所以就和之前说过的(第五章)const类型指针或者引用的形参区别实现函数重载的.

```C++
class A{
	public:
		void func();
		void func() const;
};
```
实际上是
```C++
class A{
	public:
		void func(A *const this);
		void func(const A *const this);
};
```
所以可以是重载的一点也不奇怪了.

##类类型
两个类的实际内容即使完全一样也是两个不同的类型,在类中类还是一个不完全的类型,只能使用该类型的引用或者指针或者作为参数和返回值类型.因为编译器会先把所有成员变量和函数声明扫一遍之后才开始进入各部分的定义.

##名字查找
成员函数中使用的名字,查找分三步,显示本函数内部查找,然后是类内查找,最后是全局域查找,如果函数内部名字屏蔽了类内的名字,可以使用this->name直接使用类内名字,同样可以使用::name使用全局名字.

##聚合类
*	所有成员变量都是public
*	没有定义任何构造函数
*	没有类内初始值
*	没有基类,也没有virtual函数

活脱脱一个C风格的struct.

##静态成员
*	静态成员是独立于具体类对象的,是类的固有性质,静态的成员变量不存储在对象内存中,所以sizeof(A)时候不会统计其静态成员变量的大小.
*	静态成员函数禁止使用this指针,因为它和具体对象是无关的嘛,自然也不能声明为const的.
*	静态成员函数和成员变量可以像普通变量和函数一样被其他成员函数使用或者类的对象使用.

```C++
class A{
	public:
		static int value;
};

A a;
cout<<a.value<<endl;
```

*	静态成员变量存活于程序运行的整个生命期,被所有该类的对象共用.
*	静态成员变量的类内初始化: 只有是static const整型(或可以提升为整型)变量才可以类内初始化.一般都是在类外显式的初始化(声明并定义).

```C++
class A{
	public:
		static int a;
};

int A::a = 1; //必须再次声明并定义,如果不是声明再定义,那么就相当于是赋值了.
```

*	静态成员变量和非静态成员变量的区别:
	*	静态成员变量的类型可以是该类,而非静态成员变量不行(不完整类型)
	*	静态成员变量可以作为成员函数的默认值,非静态成员变量不行

```C++
class A{
	public:
		A(const A& val = value){} //使用静态成员变量作为默认参数
	private:
		static A value; //使用不完整类型A
};
```

##其他
成员函数有很多修饰符,比如inline, virtual, const, static, explicit等,这些修饰符在成员函数声明时候肯定是要加上的(inline除外),但是在类外的函数定义处有些则不允许再加上,有些必须加上,有些不做要求.

|修饰符|声明|定义|
|:--:|:--:|:--:|
|const|必须有|必须有|
|inline|必须有|可以有|
|static|必须有|不能有|
|explicit|必须有|不能有|
|virtual|必须有|不能有|

