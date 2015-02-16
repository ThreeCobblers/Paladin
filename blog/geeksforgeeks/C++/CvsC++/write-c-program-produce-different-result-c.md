写一个程序,在C和C++编译器中都可以编译和运行,但是运行结果不一样

1)**字符常量在C和C++中是不用的,在C中被看成int,而在C++中被看成char**

```C++
#include<stdio.h>
int main()
{
  printf("%d", sizeof('a'));
  return 0;
}
```
上面这段代码在C编译器编译运行后输出4,而在C++编译器输出1

2)**在C中结构体被声明定义之后,我们定义该结构体的变量时候需要带上关键字struct,但在C++中不用**

```C++
#include <stdio.h>
int T;
  
int main()
{
    struct T { double x; };  // In C++, this T hides the global variable T, 
                            // but not in C
    printf("%d", sizeof(T));
    return 0;
}
```
上段代码在C编译器中认为T就是全局变量那个T,而在C++中已是一个结构体类型了.

3)**bool类型的值在C和C++中也是不一样的,C中认为是一个int即4个字节,而C++中是1个字节**

```C++
// output = 4 in C (which is size of int)
printf("%d", sizeof(1==1)); 
 
// output = 1 in c++ (which is the size of boolean datatype)
cout << sizeof(1==1); 
```
