Q:	Assume you have a method isSubstring which checks if one word is a substring of
another. Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using
only one call to isSubstring (i.e., “waterbottle” is a rotation of “erbottlewat”).

A:

```
	bool isRotation(const string &str1, const string &str2){
		if(str1.length() != str2.length())	return false;
		string str = str1 + str1;
		return isSubstring(str, str2);	
	}
```

这个解法真的很棒，字符串str1的旋转之后的结果肯定属于str1+str1的子串，反过来只要是str1+str1的子串同样是str1的旋转串.

其实题目已经给你提示(isSubstring)，可惜渣渣的我还是没想到这样=.=
