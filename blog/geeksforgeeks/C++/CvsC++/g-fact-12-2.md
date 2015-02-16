C允许void*指针不显式转换的情况下赋值给其他任何类型指针,而C++不可以

例如:C中代码
```C++
void* ptr;
 /* Implicit conversion from void* to int* */
int *i = ptr;
/* Implicit conversion from void* to int* */
int *j = malloc(sizeof(int) * 5); 
```
而在C++中必须要这样
```C++
void* ptr;
int *i = (int *) ptr;
int *j = (int *) malloc(sizeof(int) * 5);
```
