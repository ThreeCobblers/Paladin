#关联容器
关联容器中的元素按照关键字保存和访问的,顺序容器按照保存的位置来访问的.关联容器主要有2x2x2一共8种,分别是:
`map,set,multimap,multiset,unordered_map,unordered_set,unordered_multimap和unordered_multiset`.

##关联容器概述
*	有序容器的键值类型必须定义元素比较的方法(<, ==), 无序容器的键值类型必须定义元素相等判断方法(==)
*	pair类型:
	*	pair<T1, T2> p; 
	*	pair<T1, T2> p(v1, v2);
	*	make_pair(v1, v2);
	*	p.first, p.second
	*	p1 relop p2; 两个pair相比较,先比较first,再比较second

##关联容器操作
*	关联容器的类型别名
	*	key_type: 键值类型
	*	mapped_type: 关联值类型(只适用于map)
	*	value_type:	值类型(对于map是pair<key_type, mapped_type>, 对于set是key_type)
*	关联容器的迭代器
	*	map容器的迭代器指向value_type,是个pair,该pair的第一项指向的key_type是不能修改的,只能修改其第二项指向的mapped_type
	*	set容器的迭代器指向value_type,其实就是key_type,它也是不能被修改的.
	*	可以通过迭代器从begin到end的遍历,有序容器是按照升序的顺序排列好的.
	*	我们通常不对关联容器使用泛型算法,主要是因为其迭代器指向的key_type不能被修改,只适用于某些只读的算法.
*	关联容器添加元素
	*	insert(v), 插入value_type类型的变量v
	*	insert(b, e), 插入value_type类型的迭代器区间
	*	以上插入函数的返回值是一个pair<value_type, bool>, 第一项指向插入位置的迭代器,第二项为true表明插入成功,第二项为false表明未成功(比如以前已有此元素)
*	关联容器删除元素
	*	erase(k), 删除某个key_type类型的变量k
	*	erase(p), 删除某个迭代器指向的位置
	*	erase(b, e), 删除迭代器区间指向的区域
	*	erase返回值表明删除的元素的个数,如果是0,则表明无相关元素在容器里
*	关联容器访问元素
	*	map容器可以使用key_type作为下标访问mapped_type
		*	[key_type], 若key_type不在map中则会添加,并讲mapped_type初始化为默认值.
		*	at(key_type), 若key_type不在map中则会抛出out_of_range异常.
	*	find(key_type), 返回容器迭代器,指向第一个key_type为指定值的位置,若没有则返回end()
	*	count(key_type), 返回容器中存有的指定key_type值的个数,若没有则为0
	*	lower_bound(key_type)/upper_bound(key_type), 分别返回第一个不小于指定值的迭代器和第一个大于指定值的迭代器,所以等于指定值的迭代器区间是:
		[lower_bound, upper_bound)
	*	equal_bound(key_type), 返回一个pair,pair中存放指定值的迭代去区间的上下界
*	关联容器其他操作
	*	empty(), size(), max_size()含义和顺序容器一样
	*	swap, clear操作
*	无序容器
	无序容器实质上是基于hash 表实现的.
	*	无序容器的管理操作
		*	bucket_count(), 正在使用的桶的数目
		*	bucket_size(n), 第n个桶盛放的元素个数
		*	bucket(k), 关键字k放在哪个桶中
		*	load_factor(), 哈希表的负载系数
		*	rehash(n), 重新哈希,使得桶数目大于等于n
		*	reserve(n), 重新存储,使得可以无序容器可以保存n个元素,且不rehash
	*	无序容器不仅要求关键字可以比较==,还要可以被hash对象生成每个哈希值.
	*	构造无序容器时候还可以指定hash函数和比较运算符:
```C++
//自定义hash函数
int hasher(int value){
        return value;
}

//自定义==函数
bool k_equal(int a, int b){ 
    return a == b;
}

//前面存放类型,后面实例化具体函数指针
unordered_set<int, decltype(hasher)*, decltype(k_equal)*> 
s(100, hasher, k_equal);

```
