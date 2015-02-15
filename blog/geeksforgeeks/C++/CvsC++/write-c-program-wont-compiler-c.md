虽然C++是基于C设计的,但是仍然存在很多代码可以在C编译器编译过去,但是在C++编译不过去,下面列出的几个例子都是属于这一类.

1) **在C++中在调用未声明的函数会编译出错,但是在C中可能能编译成功.**

```C++
#include<stdio.h>
int main()
{
   foo(); // foo() is called before its declaration/definition
} 
 
int foo()
{
   printf("Hello");
   return 0; 
}
```

2)	**在C++中非const指针不能被const指针赋值,但是在C中可以**

```C++
#include <stdio.h>
 
int main(void)
{
    int const j = 20;
 
    /* The below assignment is invalid in C++, results in error
       In C, the compiler *may* throw a warning, but casting is
       implicitly allowed */
    int *ptr = &j;  // A normal pointer points to const
 
    printf("*ptr: %d\n", *ptr);
 
    return 0;
}
```

3)	**C++的const变量在定义时候必须赋初值,但是C中无此规定**

```C++
#include <stdio.h>
int main()
{
    const int a;   // LINE 4
    return 0;
}
```

4)	**C中一个void\*指针可以直接赋值给任意指针,但是C++不行,需要显示转换**

```C++
#include <stdio.h>
int main()
{
   void *vptr;
   int *iptr = vptr; 
   //In C++, it must be replaced with int *iptr=(int *)vptr; 
   return 0;
}
```

5)	**C++有一些C没有的关键字,像new, delete等,自然这些以这些关键字为变量名的代码在C++编译不过**

```C++
#include <stdio.h>
int main(void)
{
    int new = 5;  // new is a keyword in C++, but not in C
    printf("%d", new);
}
```

6)	**C++的类型转换检查要强与C,像下面的程序转换就不能通过,需要reinterpret_cast显式转换才可以**

```C++
#include <stdio.h>
int main()
{
    char *c = 333;
    printf("c = %u", c);
    return 0;
}
```
