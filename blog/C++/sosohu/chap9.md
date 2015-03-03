#顺序容器
C++的容器分类两大类,顺序容器和关联,顺序容器主要有vector, string, deque和list,另外通过这四个适配出三种顺序容器:stack, queue和priority_queue.在C++11新标准中还纳入了forword_list和array这两种顺序容器.

##顺序容器的选择
选择哪种顺序容器,要根据实际需要和结合各容器的优缺点.vector的优势在于随机访问,但是除了尾部添加/删除以外,其他位置的添加删除都很低效;list的删除和插入都很快,但是不能随机访问;deque和vector比较类似,区别在于在头部添加/删除也很方便;string和vector几乎一样,唯一区别是盛放字符比较合适;stack,queue和priority_queue一般和算法紧密结合,像递归改循环,遍历树等.

##顺序容器的通用部分
*	类型别名
	*	size_type
	*	difference_type
	*	value_type
	*	reference
	*	const_reference
	*	iterator
	*	const_iterator
*	构造函数
	*	C c;
	*	C c1(c2);
	*	C c1(b, e);
	*	C c(n); //顺序容器
	*	C c(n, i); //顺序容器
*	大小
	*	size()
	*	max_size()
	*	empty()
*	修改
	*	insert()
	*	erase()
	*	clear()
	*	swap()
	*	=
*	关系运算符
	*	==
	*	!=
	*	<
	*	\>
	*	<=
	*	\>=
*	迭代器
	*	begin()/rbegin()/cbegin()
	*	end()/rend()/cend()

##顺序容器的操作
顺序容器上的操作很多,还是要多用多练习才行.
