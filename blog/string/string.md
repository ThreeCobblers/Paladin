#string类的简单实现

##介绍
相关介绍引自陈硕的[blog](http://coolshell.cn/articles/10478.html):
>C++ 的一个常见面试题是让你实现一个 String 类，限于时间，不可能要求具备 std::string 的功能，但至少要求能正确管理资源。具体来说：

>能像 int 类型那样定义变量，并且支持赋值、复制。
>能用作函数的参数类型及返回类型。
>能用作标准库容器的元素类型，即 vector/list/deque 的 value_type。（用作 std::map 的 key_type 是更进一步的要求，要重载>运算符等,本文从略)

>换言之，你的 String 能让以下代码编译运行通过，并且没有内存方面的错误。

```C++
void foo(String x){}
 
void bar(const String& x){}
 
String baz()
{
  String ret("world");
  return ret;
}
 
int main()
{
  String s0;
  String s1("hello");
  String s2(s0);
  String s3 = s1;
  s2 = s1;
 
  foo(s1);
  bar(s1);
  foo("temporary");
  bar("temporary");
  String s4 = baz();
 
  std::vector<String> svec;
  svec.push_back(s0);
  svec.push_back(s1);
  svec.push_back(baz());
  svec.push_back("good job");
}
```

##确定要求
从上面的要求可以看出,起码要设计实现`构造函数`,`拷贝构造函数`,`重载赋值运算符`,`析构函数`等,并且要负责管理和释放所有资源

我们可以设计string类里面有一个char* data成员变量,构造函数和析构函数分别为它new和delete资源,其他的需要注意的就是在拷贝构造或者赋值时候需要`深拷贝`.

##代码

```C++
// 仿照C++, string的实现
class string{
public:
	string(const char* str){
		cap = strlen(str) == 0? 1 : 2*strlen(str);
		data = new char[cap];
		strcpy(data, str);
		size = strlen(data);
	}

	string(const char* str, int len){
		cap = len == 0? 1 : 2*len;
		data = new char[cap];
		strncpy(data, str, len);
		size = strlen(data);
	}

	string(){
		cap = 1;
		data = new char[cap];
		data[0] = '\0';
		size = 0;
	}
	
	string(const string &rth){
		size = rth.length();
		cap = rth.capcity();
		data = new char[cap];
		strcpy(data, rth.toChar());
	}

	string& operator=(const string &rth){
		if(*this == rth)	return *this;
		size = rth.length();
		cap = rth.capcity();
		delete [] data;
		data = new char[cap];
		strcpy(data, rth.toChar());
		return *this;
	}

	bool operator==(const string &rth){
		return data == rth.toChar();
	}

	int compare(const string &rth){
		return strcmp(data, rth.toChar());
	}

	int compare(const char* str){
		return strcmp(data, str);
	}

	~string(){
		delete [] data;
	}

	string& operator+(const string &rth){
		char* org = data;
		int old_size = size;
		size = size + rth.length();
		if(!cap)	cap = 1;
		while(cap < size)	cap = 2*cap;
		data = new char[cap];
		strcpy(data, org);
		delete [] org;
		char* last = data + old_size;
		strcpy(last, rth.toChar());
		return *this;
	}

	string subString(int pos, int len){
		if(pos < 0 || pos >= size)	return "";
		if(!len || pos+len > size)	return "";
		return string(&data[pos], len);
	}

	void swap(string& rth){
		std::swap(data, rth.getChar());
	}

	int length() const{	return size; }

	int capcity() const{ return cap; }

	const char*	toChar() const{	return data;}

	char*& getChar(){	return data;}
private:
	char* data;
	int size;
	int cap;
};
```
