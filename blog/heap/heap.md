#堆

##定义
	堆是一个完全二叉树,按照数据的排列方式可以分为两种：最大堆和最小堆.

###最大堆
	父结点的键值总是大于或等于任何一个子节点的键值.

###最小堆
	父结点的键值总是小于或等于任何一个子节点的键值.

举例:

![](static/heap_example.jpg)

##STL中的堆算法
在C++的STL中没有专门的堆这个容器,而是借助于像vector这样的容器实现四种堆的算法:

1.	 建堆: `void make_heap(RandomAccessIterator first, RandomAccessIterator last);  
	  void make_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp );`

2.	 入堆: `void push_heap(RandomAccessIterator first, RandomAccessIterator last);  
	  void push_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp );`

3.	 出堆: `void pop_heap(RandomAccessIterator first, RandomAccessIterator last);  
	  void pop_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp );`

4.	 堆排序: `void sort_heap(RandomAccessIterator first, RandomAccessIterator last); 
	  void sort_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp );`

具体使用方法请参考[cpluscplus](http://www.cplusplus.com/reference/algorithm/).

##算法实现
在这里,我自己简单的实现了一下上面的四个堆算法,不过不是通用模板类型的函数,只是针对int类型的简单实现,目的只是为了介绍一下这四种算法的实现及其复杂度.

###make_heap
	仿照STL那样,先将要建堆的数据都放入vector中,然后对vector中数据进行建堆调整.

####建堆算法:
	我们使用自底向上的调整算法,来将heap[0, len)中的数据调整成堆,由于堆是一个完全二叉树,
	所以heap[len/2 + 1, len)肯定都是叶子节点,不需要调整,所以只需从节点len/2开始到节点0逐渐
	的调整对应节点就可以了.

####代码:
```C++
class Com{
public:
	bool operator()(const int &a, const int &b){
		return a < b;
	}
};

//堆heao中[0, len)中的数据进行建堆
void make_heap(vector<int> &heap, int len){
	Com comp;
	if(len <= 1)	return;
	int mid = len / 2 - 1; // 中间节点
	while(mid >= 0){
		int cur = mid--;
		while(cur < len){ // 调整此节点的子树
			int index = 2*cur + 1;
			if(index < len){
				if(index + 1 < len){
					if(comp(heap[index], heap[index+1])){
						index = index + 1;
					}
				}
				if(comp(heap[cur], heap[index])){
					swap(heap[cur], heap[index]);
				}else{
					break;
				}
			}
			cur = index;
		}
	}
}
```
####时间复杂度
我们设堆中元素个数为n个(即堆中元素标号为0, 1, .... , n-1),堆的高度为h(分别为第0层,第1层, ..., 第h-1层). 我们可以知道第0层节点个数有1个,第i层节点个数为<img src="http://www.forkosh.com/mathtex.cgi? 2^i">个,而第i层需要向下调整的深度为h - 1 - i. 所以我们可以得到算法时间复杂度:

<img src="http://www.forkosh.com/mathtex.cgi? T = 2^0(h-1) + 2^1(h-2) + ...+ 2^i(h - 1 -i) + ...  + 2^{h-1}(h - 1 - (h -1))">

所以有:

<img src="http://www.forkosh.com/mathtex.cgi? 2*T = 2^1(h-1) + 2^2(h-2) + ... + 2^{i+1}(h - 1 -i) + ... + 2^h(h - 1 - (h-1))">

所以有:

<img src="http://www.forkosh.com/mathtex.cgi? 2*T - T = 2^1 + 2^2 + ... + 2^{i+1} + ... + 2^(h-1) + 2^h(h - 1 - (h-1))  - 2^0(h-1)">

所以:

<img src="http://www.forkosh.com/mathtex.cgi? T = 2^1 + 2^2 + ... + 2^{h-1} - (h - 1) = O(n)">

即时间复杂度为O(n)

###push_heap
仿照STL的约定,新加入堆[0, len)的元素处于堆的最末端len-1这个位置.

那么只需要堆新加入的元素开始自下而上的调整一次树的高度就可以了.

####代码
```C++
void push_heap(vector<int> &data, int len){
	Com comp;
	if(len <= 1)	return;
	int cur = len - 1;
	while(cur > 0){
		int parent = (cur - 1) / 2;
		if(comp(data[parent], data[cur])){
			swap(data[parent], data[cur]);
			cur = parent;
		}else{
			return;
		}
	}
}
```
时间复杂度O(lgn)

###pop_heap
仿照STL的约定,堆[0, len)被pop出去的元素要放在堆的最末端len-1这个位置.

那么只需要将堆顶元素和len-1位置的元素互换,再从堆顶开始自上而下的调整一个树的深度次即可.

####代码
```C++
void pop_heap(vector<int> &data, int len){
	Com comp;
	if(len <= 1)	return;
	swap(data[0], data[len - 1]);
	int cur = 0;
	while(cur < len / 2){
		int index = 2*cur + 1;
		if(index < len){
			if(index + 1 < len){
				if(comp(data[index], data[index+1])){
					index = index + 1;
				}
			}
			if(index == len - 1)	return;
			swap(data[cur], data[index]);
		}
		cur = index;
	}
}
```
时间复杂度O(lgn)

###sort_heap

每次将堆顶(最大值)元素pop出去,pop出去len-1次即可,使得[0, len)里面元素有序.

####代码
```C++
void sort_heap(vector<int> &data, int len){
	for(auto i = len - 1; i > 0; i--){
		pop_heap(data, i);
	}
}
```
时间复杂度O(nlgn)
