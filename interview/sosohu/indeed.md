
skype 面试

先是老美自我介绍了一下，说了他主要做什么工作，反正我也没太听懂...

然后抛来一个在线共享文档的网址，于是开始编程

>	判断一个整数数组中存不存在两个数之和等于指定的数，即2Sum问题

在问题目时候，老美比较耐心，不仅帮你定义好函数接口还帮你举了几个例子阐述一下问题

我问了几个问题，一个是数组排序的么? 无序；时间和空间复杂度有什么要求? 线性空间; 如果size为负数怎么办? 保证为正数

然后我就写代码:

```C++
bool hasSum(int values[], int size, int target){
	unordered_set<int> table;
	for(int i = 0; i < size; i++){
		if(table.count(target - values[i]))
			return true;
		table.insert(values[i]);
	}
	return false;
}
```

然后，他问了一下时间复杂度？我说是O(n); hash table的count和insert函数的时间复杂度? 平均情况O(1);
最坏情况呢? 最坏情况需要增加hash table的bucket所以要拷贝原有的所有数据，会是O(k), k是hash table中存放的数据量

Follow up: 如果是判断是否存在两数之积为某个数呢？　还能不能用这个办法？

我一开始说，会有问题，但是后来又说没啥问题，只需要注意一些精度等问题

然后，我写代码：

```C++
bool hasTime(int values[], int size, int target){
	unordered_set<int> table;
	for(int i = 0; i < size; i++){
		if(values[i] == 0){
			if(size > 1 && target == 0)	return true;
		}else{
			int remain = target / values[i];
			if(table.count(remain) && remain * values[i] == target)
				return true;
		}
		table.insert(values[i]);
	}
	return false;
}
```

最后让我问几个问题，关于在日本工作等

我问了他们公司文化怎么样
