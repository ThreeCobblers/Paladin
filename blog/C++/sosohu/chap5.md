#语句
##条件语句
else语句和最近的未匹配的if匹配,if和else语句后面要跟上{},这是良好的编程习惯.
##switch语句
switch语句每个case的作用域是在整个switch语句有效,但是如果在一个case定义并初始化(string,vector这种含有隐式初始化的也一样)某个变量,这是违法的.

例如:

```C++
	case 0: string v; int i = 1; break;
	case 1:  throw out_of_range("out_of_range");
	case 2: throw invalid_argument("invalid_argument");
	default:throw runtime_error("runtime_error");
```
上面的v和i的定义都是非法的,编译会出错`crosses initialization of ‘std::string v’`

其实来说,一般你的本意也不想让v在所有case都有效,所以你可以在case 0中使用{}括起来,这样就是局部有效,不会编译出错.

另外switch的变量必须是字符或者整型变量,case的值也必须是整型常量表达式.

##try,throw和catch语句
异常处理语句是成熟的软件代码中司空见惯的事,程序出错一般有三种处理方式:

*	返回值返回错误类型: 很多API都是这样做的,一般返回0都是运行正确,非0有错.
*	修改全局变量标明错误类型: 有某个全局变量,出错时候修改它的值.
*	try和catch语句: 这是推荐的做法,但是比较繁琐,而且不是所有语言都支持.

try语句块:	异常处理的语句块,里面放着正常的代码,和出错时候的throw语句,它包含多个catch语句块.
throw语句块:	抛出异常,希望被catch捕获.throw后面紧跟一个表达式,此表达式的类型就是异常类型.
catch:	catch括号内放着异常类型变量,用来处理相应类型异常抛出.
termiante: 没有被捕获异常发生时,程序会调用termiante()函数,终止代码,并报告出现异常的类型.

常见的异常类型有很多,像<stdexcept>文件里面的runtime_error, overflow_error, invalid_argument等.
