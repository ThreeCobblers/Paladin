每个常量字符在C/C++中都有一个类型信息,不像普通数字常量是int类型,例如`sizeof(10)`在C/C++中都是4,即int类型.但是字符常量的类型就不同了,C中字符常量的类型是int,而在C++中是char.

```C++
int main()
{
   printf("sizeof('V') = %d sizeof(char) = %d", sizeof('V'), sizeof(char));
   return 0;
}
```
上段代码在C和C++编译器运行结果分别如下:
```C++
C result – sizeof(‘V’) = 4 sizeof(char) = 1

C++ result – sizeof(‘V’) = 1 sizeof(char) = 1
```

同样,对于重载函数也是会发生这种情况,字符常量优先匹配为char类型,例如:

```C++
void foo(char c)
{
   printf("From foo: char");
}
void foo(int i)
{
   printf("From foo: int");
}
 
int main()
{
   foo('V');
   return 0;
}
```
编译调用的函数是`void foo(char);`,因为'V'是char类型的.
