#动态内存

##智能指针
在C++中我们经常需要使用动态内存,如果是直接的使用话容易忘记或者因为异常未能释放动态内存,所以需要使用智能指针来管理着动态内存.除了以前的auto_ptr以外C++11新标准中又添加了三种智能指针shared_ptr,unique_ptr和weak_ptr.

###shared_ptr
顾名思义,是共享性质的智能指针,多个shared_ptr可以指向同一块内存,通过记数的方式实现内存管理.

*	shared_ptr的操作
	*	shared_ptr<T> p;
	*	shared_ptr<T> p(u);  // 从unique_ptr那里接管,unique_ptr被置空
	*	shared_ptr<T> p(q); // q可以是另外一个shared_ptr或者是内置指针
	*	shared_ptr<T> p(q, d); // q含义同上, d是自定义的释放函数,用来一些自定义的释放.
	*	*p; //像普通指针一样解引用
	*	p.get(); //获得p中保存的指针
	*	p.swap(q);
	*	make_shared<T>(args); //申请动态内存,返回一个shared_ptr,使用args初始化此块内存的对象,比如shared_ptr<int> p = make_shared<int>(2);
	*	p.reset(); //置空p,如果p是唯一指向其对象的智能指针,则释放该对象.
	*	p.reset(q); //置p的值为q,如果p是唯一指向其对象的智能指针,则释放该对象.
	*	p.unique(); //是否唯一
	*	p.use_count(); //共享的数目
*	shared_ptr拷贝或者赋值时候引用记数都++,销毁时候--, 当减为0时候销毁相关内存.
*	由于程序在出现异常时候能够保证局部变量都被执行析构函数,所以使得智能指针管理的内存可以在异常发生后被释放,显式的使用new/delete那种方式则不能保证.

###直接管理内存
我们可以直接使用new/delete管理动态内存.
*	new动态内存: `T *p1 = new T; T *p2[10] = new T[10]; const T *p3 = new const int(10)`;
*	delete释放内存:	`delete p1; p1 = NULL; delete [] p2; p2 = NULL; delete p3; p3 = NULL;`
*	delete之后还要注意设置相应指针为NULL,防止空悬指针,其实delete之后相应内存还是在的,还是可以被使用的,只不过被标记为未用状态,好被下次申请.
*	另外delete还容易出现重复delete的现象,即多次delete同一块内存,这也会出错
从上面可以看出,直接使用new/delete问题重重,推荐使用智能指针.

###shared_ptr和new混合使用
使用方法如: `shared_ptr<T> p(new T);`这个转换是explicit的.

Note:	不要混合使用普通指针和智能指针,比如像下面的错误:
```C++
void func(shared_ptr<int> p){
	...
}

int *p = new int;
func(shared_ptr<int> tmp(p));
//临时变量tmp和函数func的局部参数变量p都销毁了,
//shared_ptr的记数为0,会释放p指向的内存
*p = 2; //出错

```

Note:	不要使用get的返回值初始化另外一个shared_ptr,这样初始化,shared_ptr个数增加了,但是引用记数没增加,会提前释放对象.

Note:
	
*	不要使用相同的内置指针初始化或者reset多个shared_ptr.
*	不要使用get()返回的指针初始化或者reset其他的shared_ptr.
*	不要delete get()返回的指针.
*	get()返回的指针使用过程中可能会失效,因为其关联的shared_ptr都销毁了.
*	如果智能指针管理的资源不是new分配的,不要忘记传递一个自定义的删除器.

###unique_ptr
unique_ptr和shared_ptr最大的不同就是每一时刻只能有一个unique_ptr指向相应对象.

*	unique_ptr的操作
	*	unique_ptr<T> p;
	*	unique_ptr<T, D> p(d); //使用专门的d来代替delete
	*	p = nullptr; //释放p指向的对象,将p置空
	*	p.release(); //p放弃对其对象的控制权,返回该对象的指针,并将p置空
	*	p.reset(); //释放p指向的对象
	*	p.reset(q); //释放p指向的对象,改为管理q指向的对象
*	unique_ptr除了拷贝或者赋值一个将要被销毁的unique_ptr以外,禁止拷贝和赋值,比如作为函数的返回值.
*	auto_ptr和unique_ptr十分类似,可以说unique_ptr是auto_ptr的超集,auto_ptr不允许任何的拷贝和赋值.

###weak_ptr
弱性只能指针,它用于绑定到某个shared_ptr,但是不会增加其记数,主要用来核查该对象是否被销毁了.

*	weak_ptr常用操作
	*	weak_ptr<T> p;
	*	weak_ptr<T> p(sp); //使用某个shared_ptr初始化
	*	p = sp;
	*	p.reset(); //置为空
	*	p.use_count(); //查看相应对象的shared_ptr数量
	*	p.expired(); //如果use_count == 0, 返回true,否则false
	*	p.lock(); //如果expired为true返回一个空的shared_ptr, 否则返回一个指向相应对象的shared_ptr
*	weak_ptr不参于shared_ptr的记数,通常是作为一个观察者的角度检测资源的使用情况.

##动态数组
前面提到的大多都是申请一个对象空间,下面介绍如何申请连续的对象.
###new/delete
```C++
	T *p[10] = new T[10];
	delete [] p;
```
###使用智能指针
*	unique_ptr<T[]> p(new T[10]);
*	shared_ptr不能直接管理动态数组,如果要管理,必须传递一个删除器:

	`shared_ptr<int[]> sp(new int[10], [](int * p){delete [] p;})`

	另外,shared_ptr的动态数组还不支持下标操作,只能使用get() + i曲线实现.

##allocator类
前面的动态内存的申请都是申请和初始化一起完成的,对于动态数组的分配前面的方法都是调用默认的构造函数,但是如果对象没有默认的构造函数怎么办?因此C++还提供一种分开的方式,allocator类将分配和构造初始化分开.

*	allocator类常用函数
	*	allocator<T> a;
	*	a.allocate(n); //分配n*sizeof(T)大小的未构造的空间,返回首地址 
	*	a.deallocate(p, n); //释放从p开始的n*sizeof(T)的空间
	*	a.construct(p, args); //根据args参数对p指向的对象进行构造
	*	a.destroy(p); //析构p指向的对象
*	使用示例
```C++
int main(){
    allocator<string> alloc;
	//分配空间
    auto p = alloc.allocate(2);
    auto q = p, r = p;
	//逐个构造
    alloc.construct(p++, "hello");
    alloc.construct(p++, "world");
    cout<<*q<<*(q+1)<<endl;
	//逐个析构
    while(q != p)
        alloc.destroy(q++);
	//释放空间
    alloc.deallocate(r, 2); 
}
```
*	拷贝和填充未初始化内存
	*	uninitialized_copy(b, e, b2);  [b2, e2) -> [b, e)
	*	uninitialized_copy_n(b, n, b2); [b2, b2+n) -> [b, b+n)
	*	uninitialized_fill(b, e, t); [b, e) <- t
	*	uninitialized_fill_n(b, n, t); [b, b+n) <- t
