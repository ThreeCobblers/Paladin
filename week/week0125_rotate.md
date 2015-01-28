###字符串旋转----求逆法

####问题
    给定字符串S，将S右/左旋m个字符，要求空间复杂度O(1),时间复杂度O(n)。关于这个问题网上有种称为"杂技法"的解决方法，但是感觉逻辑较为复杂，今天我们介绍一种通过求逆来解决该问题的方法

####求逆法
给定

字符串<img src="http://www.forkosh.com/mathtex.cgi? S=s_1s_2...s_n">， <img src="http://www.forkosh.com/mathtex.cgi? m'=m\%n">，由于可能<img src="http://www.forkosh.com/mathtex.cgi? m\geqslant n">，因此这里取模

假设这里右旋<img src="http://www.forkosh.com/mathtex.cgi? m'">个字符，则

<img src="http://www.forkosh.com/mathtex.cgi? ratate(S, m')=s_{n-m'+1}s_{n-m'+2}...s_ns_1s_2...s_{n-m'}">

令<img src="http://www.forkosh.com/mathtex.cgi? S_2=s_{n-m'+1}s_{n-m'+2}...s_n, S_1=s_1s_2...s_{n-m'}, S=S_1S_2">

很容易看出

<img src="http://www.forkosh.com/mathtex.cgi? \{S_1^{-1}S_2^{-1}\}^{-1}=S_2S_1=s_{n-m'+1}s_{n-m'+2}...s_ns_1s_2...s_{n-m'}=ratate(S, m')">

因此三次求逆就可以在O(1)的空间复杂度下完成旋转

####C代码
```
char *Reverse(char *s, int b, int n)
{
    char *p = s + b;
    char *q = s + b + n - 1;
    while(q > p) {
        char t = *p;
        *p++ = *q;
        *q-- = t;
    }
    return s;
}
char *Rotate(char *s, int n, int m) {
    m = m % n;
    if(m == 0) return s;
    Reverse(s, 0, n - m);
    Reverse(s, n - m, m);
    Reverse(s, 0, n);
    return s;
}
```
