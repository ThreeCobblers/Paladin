#重载运算与类型转换
重载运算符是具有特殊名字的函数,它的名字由关键字operator和运算符共同组成,像普通运算符一样重载的运算符也分一元/二元运算符(三目运算符无法被重载).

##基本概念
*	重载运算符可以是类的成员函数,也可以是非成员函数(一般作为友元).如果是类的成员函数,那么运算符的第一个运算对象(左侧)绑定到隐藏的this指针上,因此此时运算符显式参数比运算符操作数少1个,且此时要求这第一个运算对象必须是该类的对象;如果是非成员函数,则第一个参数是左侧对象,第二个参数是右侧对象.
	*	运算符+是A的成员函数
```C++
A a, b;
//等效于a.operator+(b)
//要求a必须是A的对象
a + b; 
```
	*	运算符+是A的友元函数
```C++
A a, b;
//等效于operator+(a, b)
a + b;
```
*	重载的运算符之间的优先级和结合律和对应内置运算符的一样.
*	不能被重载的运算符: `::`, `.*`, `.`, `? :`
*	不建议(虽然可以)被重载的运算符: `&&`, `||`, `,`, `&`
*	其它运算符基本都没什么要求: 比如`->`, `new`, `new []`, `delete`, `delete []`, `+=`等等
*	哪些重载运算符函数该作为成员函数?哪些不该?
	*	赋值,下标,调用,成员访问运算符必须是成员函数
	*	复合赋值运算符推荐是成员函数
	*	改变对象状态的,比如++,解引用等推荐是成员函数
	*	具有对称性的运算符,例如算术,判断运算符推荐是非成员函数
	*	运算符左边不是类对象的推荐是非成员函数,例如输入输出运算符

##重载输入输出运算符
废话少说,直接上例子:

```C++
class D{
	friend ostream& operator<<(ostream &os, const D& d);
	friend istream& operator>>(istream &is, D& d);
	public: 
		explicit D(int data = 0) : data(data){}
	private:
		int data;
};

//返回输出流引用用来连续输出
ostream& operator<<(ostream &os, const D& d){
	os<<d.data;
	return os;
}

//输入运算符函数要处理输入异常
istream& operator>>(istream &is, D& d){
	is>>d.data;
	if(!is){
		d = D();
	}
	return is;
}
```
因为输入和输出运算符的第一个运算对象并不是类D的对象,所以无法作为成员函数实现,所以借助友元函数实现.

##算术和关系运算符
算术和关系运算符的运算对象一般都是被读取而不写入改变,所以一般来说运算对象都是const的,自然实现方式也就是友元函数那种了.
```C++
class A{
	friend A operator+(const A& lhs, const A& rhs);

	friend bool operator==(const A& lhs, const A& rhs);

	public:
		explicit A(int data = 0) : data(data) {}
		//复合赋值运算符
		A& operator+=(const A& rhs){
			data += rhs.data;
			return *this;
		}

	private:
		int data;
};

//算术运算符一般通过复合赋值运算符实现
A operator+(const A& lhs, const A& rhs){
	A sum = lhs;
	sum += rhs;
	return sum;
}

bool operator==(const A& lhs, const A& rhs){
	return lhs.data == rhs.data;
}
```

##赋值运算符
赋值运算符要改变对象的状态,要求定义为成员函数,复合赋值运算符推荐定义成成员函数.使用示例见上章拷贝控制部分和上面的例子中的+=复合赋值运算符

##下标运算符
下标运算符通常会定义出两个版本:const版本和非const版本,所以它要求必须是成员函数.
```C++
class E{
	public:
		E(int n = 0) : data(vector<int>(n)) {}

		int& operator[](int n){
			return data[n];
		}

		const int& operator[](int n) const{
			return (*(const_cast<E*>(this)))[n];
		}
	private:
		vector<int> data;
};
```

##递增递减运算符
*	递增递减运算符推荐使用成员函数
*	前置和后置递增/递减通过哑元来区别,另外根据前置后置区别,前置返回值是对象引用,后置返回值是对象的拷贝.
```C++
class A{
	public:
		A(int data = 0) : data(data) {}
		//前置++
		A& operator++(){
			data++;
			return *this;
		}
		//后置++
		A operator++(int){
			A tmp = *this;
			++(*this);
			return tmp;
		}
	private:
		int data;
};

A a;
//等效于a.operator++(0)
a++;
//等效于a.operator++()
++a;
```

##成员访问运算符
成员访问运算符`->`必须是成员函数,一般借助于解引用运算符实现
```C++
class F{
	public:
		F(string str = "") : data(new string(str)) {}
		~F(){ delete data;}
		
		string& operator*(){
			return *data;
		}
		//重载访问运算符
		string*	operator->(){
			return &(this->operator*());
		}
		
	private:
		string* data;
};
```

##函数调用运算符
函数调用运算符也可以重载,使得类像一个函数一样被调用,称为函数对象,一个类可以定义多个不同版本的调用运算符,只要相互之间在参数类型和数量上区别.函数对象常常用作泛型算法的实参.

*	lambda表达式其实就是通过构造一个匿名的函数对象实现的.
```C++
vector<int> v;
sort(v.begin(), v.end(), [](int i, int j){ return i < j;})
```
实质上会被编译器变成:
```C++
vector<int> v;

class Comp{
	public:
		bool operator()(int i, int j){
			return i < j;
		}
};

//函数对象生成一个临时对象作为形参
sort(v.begin(), v.end(), Comp());
```
*	标准库中有很多模板类都是函数对象,比如greater<type>类, plus<type>类等等
*	函数,函数指针,函数对象类型是不同的,但是调用方法是一样的.新标准中使用function类型来统一接受它们.

##类型转换运算符
还有一类特殊的运算符,就是类型转换运算符.其形式是:`operator type() { ... }`,type是除了void以外任何可以做函数返回类型的类型,即不能是数组类型,可以是数组指针等.
*	类型转换函数必须是类的成员函数
*	类型转换函数没有形参和返回类型,一般来说是const的
```C++
class A{
	public:
		A(int data = 0) : data(data) {}

		operator int(){
			return data;
		}
	private:
		int data;
};

A a;
//发生隐式类型转换
int i = a + 3;  
```
*	新标准引用explicit修饰类型转换函数,用来抑制隐式转换(用作条件判断是不抑制).
```C++
class A{
	public:
		A(int data = 0) : data(data) {}

		explicit operator int(){
			return data;
		}
	private:
		int data;
};

A a;
//显式类型转换
int i = static_cast<int>(a) + 3;  
```
类型转换函数常见用法就是类型转为bool类型,可用作判断.

##类型转换和函数重载的二义性
类型转换一定要谨慎,弄不好就是弄出二义性来,需要注意以下几个方面:

*	不要令两个类型执行相同的类型转换
*	如果已经有一个算术类型转换函数,不要再定义接受算术类型或转出算术类型的函数.
*	有时候类型转换和重载运算符结合起来会形成二义性
