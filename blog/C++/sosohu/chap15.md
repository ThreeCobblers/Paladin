#面向对象程序设计
面向对象设计的核心是数据抽象,继承和动态绑定.数据抽象使得类的接口和实现分离,继承可以定义相似的类型,并对其相似关系建模,动态绑定可以一定程度上忽略相似类型的区别以统一的方式使用它们的对象.

##OOP概述
*	继承
	*	基类与派生类
	*	类派生列表: 冒号+继承访问说明符+基类, 例如`class B : public A`中的` : public A`
	*	派生类的声明仅仅是`class B;`, 不包含类派生列表
	*	虚函数: 具有virtual修饰的成员函数称为虚函数,和普通函数不同,即使虚函数不会被调用也要有定义,不能仅仅有声明.
*	动态绑定: 只有基类的指针或者引用调用虚函数时候才会发生动态绑定,其具体执行函数要等到运行时才得到确定.

##基类和派生类
*	基类通常要定义一个虚析构函数.
*	基类中的成员函数一般分为两类,一类是希望被继承类覆盖的函数一般声明为虚函数;另一个是希望被继承类直接继承的普通成员函数.
*	基类的public和protected成员都可以被派生类及派生类的友元访问,private成员则不行.这与类派生列表中的继承访问说明符没有关系.
*	基类的虚函数一般在派生类需要重新定义,而且和基类的形参要求完全匹配,返回类型除了是类指针或引用可以不同外,其余必须相同.如果有不匹配的地方,那么派生类的这个函数和基类的那个虚函数就没有关系,不能被动态绑定了.新标准中使用override函数修饰符可以规避这个错误.
*	我们可以用基类指针或者引用绑定到派生类对象上.
*	派生类的构造函数首先要调用基类构造函数构造基类部分的数据,再按声明顺序构造派生类的成员变量.
*	基类的static成员只有唯一的实例,它可以通过基类也可以通过派生类加`::`访问
*	派生类继承基类时,必须可见基类的定义,因为没有其定义是无法初始化基类的.
*	类定义时候可以在类名字后面加上final关键字,禁止此类再被继承
```C++
class A final{
	...
};
```

##类型转换与继承
*	静态类型和动态类型:
	*	静态类型:	变量声明时的类型,编译器时已知的.
	*	动态类型:	变量表示的实际内存中的对象类型,运行时才知道.
	*	如果变量即不是引用也不是指针,那么它的静态类型就是它的动态类型.
*	基类和派生类的相互转换:
	*	基类指针或引用可以绑定到派生类对象上(可能会由于继承访问说明符受到限制)
	*	基类指针或引用不会隐式转换为派生类指针或引用,可以使用dynamic_cast和static_cast显式的转换
```C++
class A{ };

class B : public A{};

A a;
B* b = static_cast<B*>(&a);
```
	*	派生类类型和基类类型不能转换,之所以我们看到有:
```C++
class A{ };

class B : public A{};

B b;
//调用A.A(const A& rhs)拷贝构造函数
A a = b;

```
是因为,调用A(const A& rhs)拷贝构造函数,而const A& rhs = b;这是将基类的引用绑定到派生类对象上,所以没有问题.

##虚函数
*	虚函数必须要有定义
*	当且仅当是通过指针或者引用调用虚函数时候才会发生运行时绑定,才可能出现动态类型和静态类型不同,其它一律使用静态类型来确定使用哪个函数.
*	派生类如果覆盖基类的虚函数,那么一定要保证形参和基类的完全匹配,函数返回值类型也要一样,除了返回值类型是类本身的引用或者指针外.
```C++
class A{
	public:
		virtual int func();
};

class B : public A{
	public:
		//与基类的不一样
		virtual int func(int);
}

B b;
A *p = &b;

//调用A::func();
p->func();

//出错,A没有func(int)成员函数
p->func(1);
```
为了避免这样的笔误,我们可以在派生类func函数中加上修饰符override,编译器会检查基类有无与它完全匹配的虚函数,若无会编译报错.
*	我们可以给成员函数加上final修饰符,使得此函数不能被派生类覆盖重写.
*	虚函数的默认实参通过静态类型确定,比如:
```C++
class H{
	public:	
		virtual void func(int n = 1) const{
			cout<<"H: "<<n<<endl;
		}
};

class G : public H{
	public:
		virtual void func(int n = 2) const{
			cout<<"G: "<<n<<endl;
		}
};

int main(){
	G g;
	H* h = &g;
	h->func();
}
```
以上程序会输入`G: 1`,所以使用的默认参数是H::func的,这是因为h的静态类型是H*,所以其使用H::func的默认参数

*	我们可以通过类名加双冒号`A::`的形式强制使用某个类的函数,回避虚函数机制,例如上面的代码`h->func()`改为`h->H::func()`则执行结果为`H: 1`,即调用了H::func()函数.

##抽象基类
*	虚函数可以在声明时候加上`= 0`(只能出现在类内部声明),使得虚函数变为纯虚函数.
*	含有纯虚函数的类是抽象基类,抽象基类不能创建抽象基类的对象.

##访问控制和继承
首先我们要明确一个类的成员有哪几方会访问:(1)类的普通用户, (2)派生类及其友元, (3)类自生成员和自身友元.

###类中的保护声明
*	类中的public成员可以被类的普通用户,派生类及其友元,类自身成员和自身友元访问.
*	类中的protected成员可以被派生类及其友元(必须通过派生类对象来访问),类自身成员和自身友元访问.
```C++
class H{
	protected:
		int data;
};

class G : public H{
	public:
		void func(const H& h) const{
			//编译会出错
			cout<<h.data<<endl;
		}

		void func(const G& g) const{
			//可以访问
			cout<<g.data<<endl;
		}
};
```
*	类中的private成员只能被类自身成员和自身友元访问.
###继承访问说明符
继承访问说明符用来控制派生类的普通用户和派生类的派生类及其友元对基类成员的访问.

下表列举类不同的继承访问说明符下派生类的普通用户和派生类的派生类及其友元对原基类的成员的访问权限

|继承访问说明符|public|protected|private|
|:----:|:---:|:----:|:----:|
|**基类成员访问说明符**||||
|**public**|public|protected|private|
|**protected**|protected|protected|private|
|**private**|private|private|private|

###派生类向基类转换的可访问性
假设基类为B,派生类为D

*	只有当D是public继承B时,用户代码(有别于下面两种情况提到的代码情形)派生类才可以向基类转换.
*	不论D以何种方式继承B,D的成员函数(这就不是用户代码)和D的友元都可以使用派生类到基类的转换.这一点也很好理解,因为对于D的成员函数和友元都已B的public成员都是可见的.
*	如果D是public或者protected继承B,则D的派生类E的成员函数或者友元可以使用D到B的转换.这个原因也很显然,因为D是public或protected继承B,那么根据上面的表格E的成员函数肯定可以访问B的public成员.

总而言之一句话: 对于某个代码节点,只要是基类的public成员都可见,那么就可以由派生类像基类转换.

###友元和继承
友元关系不能被继承,比如B是A的友元,D是B的派生类,那么D不是A的友元,即不能继承.

###改变某些成员的访问性
新标准允许我们使用using关键字可以打破上面表上规定的一些基类成员访问的限制.
```C++
class H{
	protected:
		int data;
};

class G : public H{
	public:
		using H::data;
};


G g;
cout<<g.data<<endl;
```
本来按照上面表格规定,基类的protected成员data在public继承下是protected的,不能被派生类的使用者访问的,但是在G中使用`using H::data`,并置于public权限下则变成public的了.

###默认的继承访问说明符
*	struct类的是public
*	class类的是private

##继承中的类作用域
*	派生类的作用域嵌套在基类的作用域中
*	名字查找与继承:

	在继承体系中名字查找(比如查找p->func())遵循下面的顺序:

	*	首先确定p的静态类型
	*	在p的静态类型中找func名字的成员,如果找不到继续沿着继承链向上查找
	*	一旦找到的func成员,就停止查找,进行类型检查
	*	如果检查之后发现合法,编译器还要看一下此函数func是否为virtual函数
		*	若func是virtual函数而且我们的p是指针或者引用,则编译器进行动态绑定,在运行时确定到底该运行哪个虚函数版本
		*	若不是上面的情况,则产生一个常规函数调用
	*	如果检查之后发现不合法,编译器报错(名字查找优先于类型检查)
```C++

class H{
	public:
		void func(int){}
};

class G : public H{
	public:
		void func(){}
};

G g;
g.func(1);
```
先确定g的静态类型是G,从G中开始找func,找到G::func(),名字匹配则查找结束,再进行类型检查,发现不匹配,则编译器报错.

**C++的名字查找一直都是优先于类型检查,从内层作用域一层一层的往外层作用域找,直到找到名字匹配的,就停止查找,再进行类型匹配,同一个作用域如果有多个匹配成功的名字(重载),则选择那个最佳类型匹配.**

##构造函数和拷贝控制与继承
*	析构函数一般声明为虚函数
*	继承中的删除函数问题:
	*	如果基类中的默认构造函数,拷贝构造函数或赋值运算符是被定义成删除的(= delete),那么派生类对应的函数也是删除的.
	*	如果基类的析构函数是private或者删除的,则派生类的默认构造函数,拷贝构造函数,赋值运算符和析构函数都是删除的.因为它无法释放基类.
*	派生类的构造函数(拷贝构造函数)先要调用基类构造函数(拷贝构造函数)构造基类成员,再构造派生类成员.
*	派生类的赋值运算符先要调用基类赋值运算符赋值基类成员,再赋值派生类成员
*	派生的析构函数只需要析构派生类的成员,之后会隐式的调用基类的析构函数
```C++
class H{
	public:
		H(int data = 0) : data(data) {}
		H(const H& rhs) : data(rhs.data) {}
		H& operator=(const H& rhs){
			data = rhs.data;
			return *this;
		}
	private:
		int data;
};

class G : public H{
	public:
		G(int data = 0, int val = 0) : H(data), val(val) {}
		G(const G& rhs) : H(rhs), val(rhs.val) {}
		G& operator=(const G& rhs){
			//显示调用基类=
			H::operator=(rhs);
			val = rhs.val;
			return *this;
		}
	private:
		int val;
};
```
*	如果构造函数或者析构函数调用虚函数,那么此虚函数就使用与该构造函数或者析构函数同属类型对应的虚函数,不再动态绑定.
```C++
class H{
	public:
		H(int data = 0) : data(data) { func(); }
		virtual void func(){
			cout<<"H"<<endl;
		}
	private:
		int data;
};

class G : public H{
	public:
		G(int data = 0, int val = 0) : H(data), val(val) {}
		virtual void func(){
			cout<<"G"<<endl;
		}
	private:
		int val;
};

G g;
```
则上面在构造时候H::H(int)函数调用的虚函数func()是H::func(),因为此时派生类还没构造.

*	类不能继承构造函数,拷贝和移动构造函数

