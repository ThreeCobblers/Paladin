#模板

##定义模板

###函数模板
*	函数模板形式:
```C++
template <typename T>
bool comp(T a, T b){
	return a < b;
}
```
*	实例化函数模板: 我们直接给函数模板传递参数,编译器将通过推断模板参数来实例化函数模板.
*	函数模板参数:
	*	类型参数: 类型参数即可以用来指定函数的形参类型,也可以指定函数的返回值类型
```C++
template <typename R, typename T>
R comp(T a, T b){
	return a < b;
}
```
	*	非类型参数: 非类型参数可以是一个整形,也可以是一个指向对象或者函数的指针或引用;绑定到非类型整形参数的实参必须是一个常量表达式,绑定到指针或引用的非类型参数必须具有静态的生存期.
```C++
template <int N, int M>
bool comp(const char (&a)[N], const char (&b)[M]){
	return strcmp(a, b);
}

comp("hello", "world");
```
	*	函数模板和类模板成员函数的定义通常都放在头文件中
	*	只有我们在实例化出模板的一个特定化版本时候,编译器才会生成相应代码
	*	我们要保证传递给模板的实参支持模板所要求的操作,这是调用者的责任

###类模板
函数模板的类型可以通过形参推测,但是类模板的类型必须指定,不能推测

*	类模板的每个实例都是一个独立的类,彼此之间没有关系
*	默认情况下,类模板的成员函数只有在调用它时候才会实例化
*	我们在使用一个类模板类型时必须提供实参,但是在类模板自己的作用域(类模板内)中可以直接使用类模板名字而不加实参,这是一种简化模式
*	类模板和友元: 假设我们有类A和B
	*	A是非模板类,B是模板类, 在`class A{}`中:
		*	`friend class B<A>;` 表明用A实例化的一个类`B<A>`是A的友元,其他的`B<X>`一律不是A的友元
		*	`template<typename T> friend class B;` 表明所有的B实例都是A的友元
	*	A是类模板,B是类模板,在`template<typename T> class A{}`中:
		*	`friend class B<T>;` 表明每个B实例是对应A实例的友元
		*	`template<typename K> friend class B; `表明每个B实例都是每个A实例的友元
	*	A是类模板,B是非类模板,在`template<typename T> class A{}`中:
		*	`friend class B; `B是所有A的实例的友元
*	模板类型别名: 形如`typename A<int> IntB;`
*	类模板中的static成员: 每个类模板实例化之后都有其各自自己的一份属于该类的static成员,它被该类所有的对象共享.

###模板声明
*	函数模板: 形如`template<typename T> bool comp(T a, T b);`
*	类模板:	形如`template<typename T> class A;`

###模板参数
*	模板内不能重用模板参数名
*	使用模板类型参数的类型成员,需要使用关键字typename用以告知编译器是类型成员而不是静态成员.
```C++
template<typename T>
typename T::size_type func(T a){
	...
}
```
因为此时T是未知的,所以编译器无从知道size_type是类型成员还是静态成员.
*	模板的默认实参: 在新标准中,类模板和函数模板的形参都可以提供一个默认实参,使用方法同普通函数默认形参.
```C++
template<typename T = int>
class A{
	...
}

//使用默认类型实参
A<> a;
```

###成员模板
一个类(无论是普通类还是模板类)包含了一个模板成员函数,称为成员模板.
*	普通类成员模板:
```C++
class A{
	public:
		template<typename T> func(T a){}
};

A a;
a.func(2);
```
*	类模板的成员模板: 注意成员模板要另用其他类型模板形参.
```C++
template<typename K>
class A{
	public:
		template<typename T> bool func(T a){}
};

A<string> a;
a.func(2);
```
类模板的形参需要显示指明,函数模板的形参可以隐式推断


###控制实例化
模板被使用时候才会进行实例化,这意味着相同实例可能出现在多个对象文件中,这势必会增加额外的开销,新标准下我们可以**显示的实例化**

*	显示实例化形式如下:

类模板:
```C++
template<typename K>
class A{
};
```
显示实例化(仅一份):
```C++
template class A<int>;
```
外部使用
```C++
extern template class A<int>;
```

*	显示实例化之后,会实例化该模板的所有成员.

##模板实参推断
*	函数模板的类型推断是按照下面的规则:
	*	顶层const无论修饰实参还是形参都被忽略
	*	const转换:	可以将一个非const对象的指针或对象传递给一个const对象的指针或者引用的形参
	*	数组或指针转换:	如果形参不是引用类型,那么可以将一个数组或则函数类型的实参应用正常的指针转换.
	*	其他的类型转换,包括算术转换这种普通函数支持的转换在函数模板中都不支持.
```C++
template<typename T>
bool comp(T a, T b){
	return a < b;
}
//调用出错,不能算术转换
comp(1, 1.2);
```
*	函数模板可以用普通函数实参,普通函数实参的类型转换规则与普通函数的一样.
```C++
template<typename T>
bool comp(T a, int b){
	return a < b;
}
//调用成功, 1.2转为1
comp(1, 1.2);
```
*	函数模板显示实参
上面的例子都是编译器为函数模板推测形参类型,我们还可以直接显示的指定实参类型
*	显示模板实参形式:
```C++
template<typename R, typename T>
R comp(T a, T b){
	return a < b;
}
comp<bool, int>(1, 1);
```
*	显式模板实参按照由左到右的顺序与对应模板参数匹配,剩余的由函数形参推测
```C++
template<typename R, typename T>
R comp(T a, T b){
	return a < b;
}
//只给了R, T由编译器推测
comp<bool>(1, 1);
```
*	如果某个形参使用了显式实参指定,那么对应的类型转换规则就放宽了,即和普通函数的类型转换规则一样
```C++
template<typename R, typename T>
R comp(T a, T b){
	return a < b;
}
//1.2转为1
comp<bool, int>(1, 1.2);
```
*	模板实参推断与引用
	*	模板实参是左值引用: 编译器会运用正常的引用绑定规则,此时const是底层的,不是顶层的.
```C++
template<typename T>
bool comp(T a, T b){
	a = 3;//可以修改
	return a < b;
}

const int a = 2;
comp(a, a);
```
上面代码,不是引用,此时const int是顶层const被忽略
```C++
template<typename T>
bool comp(T &a, T &b){
	a = 2; //编译出错,不能修改
	return a < b;
}

const int a = 2;
//T是const int
comp(a, a);
```
上面代码,是引用,此时const是底层的.
	*	模板是右值引用

##重载与模板
*	当有多个重载模板对一个函数调用提供同样好的匹配时,应该选择最特例化的版本
*	对于一个函数调用,当一个非函数模板和函数模板提供同样好的匹配时,应该选择最特例化的版本,即非函数模板版本
*	重载的模板函数和普通函数一样,都是名字检查优先于类型检查

##模板特例化

###函数模板特例化
*	我们为函数模板特例化时候,必须为函数模板每个模板参数都提供实参,形式如:
```C++
//通用版本
template<typename T>
bool comp(T a, T b){
	...
}

//特例化版本
template<>
bool comp(int a, int b){
	...
}
```
*	函数模板的一个特例化版本其实就是实例化一个函数模板,并非重载它,因此不影响函数匹配
*	模板及其特例化版本都应该放在声明在同一个头文件中,先是模板再是特例化模板,避免找不到特例化模板而使用原模板实例化一个不是定制的特例化模板的代码从而出现错误.

###类模板特例化
*	类模板特例化举例:
```C++
//特例化std::hash
template<>
struct hash<int>{
	..
};
```
*	与函数模板一样特例化的类模板通常也是放在类模板后面,保证和类模板一样的可见性.
*	类模板部分特例化:	与函数模板不同,我们可以只指定一部分模板参数,或是参数的一部分特性.
```C++
template <typename T, typename Allocator> 
class Vec 
{ 
  /*......*/
}; 
  
// 部分特例化 
template <typename Allocator> 
class Vec<bool, Allocator> 
{ 
  /*......*/
};
```
*	特例化类模板的成员函数: 我们可以只特例化类模板的某个成员函数
```C++
template<typename T>
class A{
	public:
		void func(T a){ ... }
}

//特例化成员函数func
template<>
void A<int>func(int a){
	...
}
```
