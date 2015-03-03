#IO库
##IO类
*	include<iostream>头文件里面有着三类负责io交互的类:`iostream`,`istream`,`ostream`,分别负责IO读写,读和写.
*	IO类对象不能拷贝或者赋值.
*	IO库条件状态:IO库提供很多函数来查询和设置IO状态.
*	cin和cout分别是istream和ostream类型对象,它们执行输入输出后会返回一个bool值,用以判定执行的成功与否
*	触发输出刷新的几种可能:
	*	程序正常运行结束(如果是异常结束,可能有些输出未刷新出来)
	*	遇到endl类似的操纵符
	*	缓冲区满
	*	输出流对象(cout)被设置为unitbuf,例如:cout<<unitbuf; 另外像cerr就是这类
	*	遇到相关联的流,比如cout与cin是关联的(cin.tie(&cout)),当遇到cin时候,之前的cout要刷新出来.

##文件输入输出
*	include<fstream>包含这三种操作文件输入输出的类,分别是fstream, ifstream和ofstream,它们分别继承自iostream, istream和ostream, 分别控制这文件的读写,读和写.
*	fstream in(filename, mode): 以mode模式打开filename文件,也可以先fstream in; in.open(filename, mode),可以直接通过in的bool值判断是否打开成功.
*	fstream还提供几个函数,close用来关闭文件流,is_open()检查文件是否打开.
*	常见的mode有: in(输入), out(输出), app(追写), ate(定位最后), trunc(截断), binary.用之前要加上fstream::.

##string流
*	这个东西是之前没有用过的,除了IO和文件流以外还有一个与内存string交互的流.在#include<sstream>里面定义这三种控制string流的类: stringstream, istringstream和ostringstream分别继承于iostream,istream和ostream,分别控制string流读写,读和写.
*	使用istringstream示例:
```C++
	vector<string> v;
	string line;
	while(getline(cin, line)){
		//每一行字符串读入到istringstream对象中
		istringstream is(line);
		string word;
		while(is>>word){//像操作cin一样
			v.push_back(word);
		}
	}
```
*	使用ostringstream示例:
```C++
	ostringstream os;
	for(auto ele : v){
		//string写到ostringstream对象中
		os<<ele<<" ";  
	}
	//str函数打印ostringstream存储的字符串
	cout<<os.str()<<endl;
```

