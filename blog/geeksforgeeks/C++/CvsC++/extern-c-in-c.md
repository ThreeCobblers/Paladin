C++支持函数重载,C++编译器在实现函数重载时候是采用更改函数名字的方式,这项技术称为**Name Mangling**.C++标准里面并未专门指出**Name Mangling**技术,所以不同的编译器实现添加的方法也不一样.

例如下面的代码:

```C++
int  f (void) { return 1; }
int  f (int)  { return 0; }
void g (void) { int i = f(), j = f(0); }
```
在使用g++ -S编译成汇编代码之后就是:

```C++
_Z1fv:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$1, %eax
	popl	%ebp
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE0:
	.size	_Z1fv, .-_Z1fv
	.globl	_Z1fi
	.type	_Z1fi, @function
_Z1fi:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$0, %eax
	popl	%ebp
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
```

可以看到,重载的函数f分别被改为fi和fv

**在C++链接时候,如何处理C已有的符号**
在C语言中,函数是不能被重载的,所以当我们在C++中链接C代码时候要确保该符号名字没有被改变,举例说明如下:

```C++
// Save file as .cpp and use C++ compiler to compile it
int printf(const char *format,...);
 
int main()
{
    printf("GeeksforGeeks");
    return 0;
}
```
这段代码试图,声明已链接的C库的库函数,前面的意思是printf的声明,但是不要忘记这是cpp文件,所以编译器会修改该函数的名字,而修改后的函数就不叫printf了,自然在链接时候会出错.

解决办法也很简单,在声明部分套上extern "C"{}就可以了,这样就是按照C的方式处理,编译器也不会再修改函数名字了.

```C++
// Save file as .cpp and use C++ compiler to compile it
extern "C"
{
    int printf(const char *format,...);
}
 
int main()
{
    printf("GeeksforGeeks");
    return 0;
}
```

**注意**

*	因为C++要实现函数重载技术,所以编译器会改变函数名字,以避免重名函数冲突.
*	C语言部分的函数名字不能被修改,因为C语言不支持函数重载,为了避免出现像上面的错误,需要extern "C"保护起来.

