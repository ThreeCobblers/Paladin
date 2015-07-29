
##skype 面试

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

##onsite 一面
一面是一位英国人，先是自我介绍了一番，然后开始让我自我介绍，我就很简单的说了一下在哪里读书，主要做过什么等
然后他又让我介绍一下我的项目，我就结结巴巴的说了一下我的优化项目，所谈寥寥无趣吧．

然后就开始问算法题:
>	给你一个类定义如下,其中: record函数每次记录一个值val; mean函数则统计最近5 min之内记录的数值的平均值; now函数是给定的获取时间函数,返回的时间单位为ms,该函数不需你实现．　现在要求你实现record和mean函数

```C++
class Recent{
private:
	long long now();
public:
	void record(int val);
	double mean();
}
```

这道题我当初给的方案就是利用一个双向队列来记录每次record插入的值，然后根据时间来删除过期的值

```C++
class Recent{
private:
	long long now();
	deque<pair<int, long long>> data;
	double sum;

private:
	void clearOld(long long t){
		while(!data.empty()){
			auto ele = data.front();
			if(ele.second >= t){
				return;
			}else{
				sum = sum - ele.first;
				data.pop_front();
			}
		}
	}

public:
	Recent() : sum(0){}

	void record(int val){
		long long t = now();
		clearOld(t - 5*60*1000);
		data.push_back(make_pair(t, val));
		sum = sum + val;
	}
	
	double mean(){
		long long t = now();
		clearOld(t - 5*60*1000);
		if(data.empty()){
			throw exception;
		}else{
			return sum / data.size();
		}
	}
}
```

然后他又问了我record函数和mean函数的时间复杂度，我说最坏情况下为O(k), k为5分钟内的记录数．然后又问了我deque怎么实现的，我就简单的画图说了一下.

总结：	这个算法题我的做法其实还有很大的改进空间，在clearOld的时候可以采用二分法而不是一个个的清除，这样就可以把时间复杂度降到O(lgk)

##onsite 二面
二面是一个日本人，英语说的还是很好的，寒暄了几句就开始出算法题，他出题之前还扯了一下算法题的项目背景，仔细一看就是`word break`

>	给定一个字符串和一个词典，假设该字符串肯定可以被break,找出任意一种划分并返回结果

```C++
class Break{
public:
	vector<string> break(string str);
private:
	unordered_set<string> dict;
}
```

我这边采用的是动态规划的做法，O(n^2)空间和O(n^2)时间复杂度

Follow Up:
>	如果给的字符串不是一下子给定的，而是一个一个字符给定的，每给一个字符返回当前给出的字符串的任意划分. 例如分别给'h', 'e', 'i', 's';则返回[], ["he"], [], ["he", "is"]

```C++
class Break{
public:
	vector<int> canBreak(char c);
private:
	unordered_set<string> dict;
}
```

这题我的回答也还是用dp, 只不过用一个vector<int> len来记录每个字符所在词的长度，如果为０则表示不能切分，例如对于输入'h', 'i', 'm'依次输入，则len的值依次为: [0], [0, 2], [0, 2, 3], 则依次输出[], ["hi"], ["him"]

这样其实和上面的解法一样，而且还节省了空间=.=

##onsite 三面
三面直接上算法题，就是leetcode上的Median of Two Sorted Array. 这本来是一道很简单的题目，可是当时我想的不对，所以没能最终写出来...





##总结:
首先英文面，题目交流虽然有点吃力但是还好可以交流，我表达有时候很语无伦次，也反映出词汇匮乏...　其次，这几道题其实并不太难，可惜写出来并不是很顺．　最后面试的结果就是跪了，也挺伤心的...
