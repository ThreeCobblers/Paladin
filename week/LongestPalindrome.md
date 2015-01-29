#最长回文子串问题

##定义
	从字符串中找到一个长度最长的回文子串.

##算法

###Brute Force
最容易想到的就是暴力的算法,以每个可能的回文中心,找到每个回文,然后找到最长的那个回文,十分简单粗暴,就不详细介绍了.
####代码
//以前写的很糟糕=.=
```C++
	string longestPalindrome(string const& s) {
		int size = s.length();
		string str;
		if(size == 0)	return str;
		int max = 1, start = 0;
		int pre, next, cur;
		for(int i = 1; i < size; i++){
			pre = i - 1 ;
			next = i;
			cur = 0;
			while(pre > -1 && next < size & s[pre] == s[next]){
				pre--;
				next++;
				cur = cur + 2;
			}
			if(cur > max){
				max = cur;
				start = pre + 1;
			}
			pre = i - 1 ;
			next = i + 1;
			cur = 1;
			while(pre > -1 && next < size & s[pre] == s[next]){
				pre--;
				next++;
				cur = cur + 2;
			}
			if(cur > max){
				max = cur;
				start = pre + 1;
			}
		}
		return s.substr(start, max);
    }
```
时间复杂度O(n^2)

###Manacher算法
我们定义: 考查的字符串为s[0...n-1],

 那么,为了避免像上面算法那样还要考虑回文对称点处于不处于`空隙`,我们可以在原来的字符串s中插入`#`构造的新字符串为str[0...2*n]:

	str[0...2*n] = "#s[0]#s[1]...#s[n-1]#".

我们再定义数组p[0...2*n]表示str字符串中的回文情况,其中p[i]表示以str[i]位回文中心向两边能到达的最长回文距离, 例如 str = "#a#a#", 那么 p = {1,2,3,2,1}

另外,我们定义两个变量mx和id, 其中id表示最右回文子串(指的是这个回文子串是目前已发现的回文子串中最靠右的)中心的位置，mx则为id+P[id], 即回文子串的边界.

然后,我们初始化p[0] = 1, mx = 1, id = 0;

我们试图将这个问题转为一个动态规划问题,我们假设p[0...i-1]都已经求出,那么现在来求p[i],在求p[i]之前,我们已知当前id和mx, 我们设 j = id - (i - id)即i关于id的对称点. 我们已知到p[j]的值,我们可以得出结论:

	如果 i < mx 那么p[i] >= min{p[j], mx - i}

为什么就有这个结果呢?很难告诉你Manacher为什么会想到这个不等式,但是我们可以验证这个不等式.

当i < mx,则i落在以id为中心的回文串中.

*	如果 p[j] > mx - i, 那么以j为中心的回文串超出了以id为中心的回文串的区域, 因为 j - p[j] < id - (mx - i). 所以我们无法保证超出部分映射到i这边来也会有,但是我们可以保证未超出部分,也就是[j - (mx - i), j + (mx - i)]肯定是回文的,又因为j是i的对称点,所以这边也有[i - (mx - i), i + (mx - i)]也是回文的,所以p[i] >= mx - i;
*	如果 p[j] < mx - i, 那么以j为中心的回文串全部落在以id为中心的回文串中,根据i和j对称关系,这边也有一个对应的回文串,所以p[i] >= p[j];

所以证明出在 i < mx时, p[i] >= min{p[j], mx - i}

那么当i >= mx时候,那只能保证p[i] >= 1,然后对i使用简单的搜索了.

####代码
```C++
tring longestPalindrome(string const& s) {
		int n = s.length();
		if(n == 0)	return "";
		string str = "#";
		int count = 0;
		for(int i = 0; i < n; i++){
			str += s[i];
			str += '#';
		}
		int id = 0, mx = 0;
		vector<int> p(2*n+1, 0);
		p[0] = 1;
		for(int i = 1; i < 2*n + 1; i++){
			int j = 2*id - i;
			p[i] = mx > i? min(p[j], mx - i) : 1;
			while(i + p[i] < 2*n + 1 && i - p[i] >= 0){
				if(str[i + p[i]] != str[i - p[i]]) break;
				p[i]++;
			}
			if(i + p[i] > mx){
				mx = i+ p[i];
				id = i;
			}
		}
		int max = INT_MIN;
		int pos = 0;
		for(int i = 0; i < 2*n + 1; i++){
			if(max < p[i]){
				max = p[i];
				pos = i;
			}
		}
		int index, len;
		len = (max - 1);
		index = pos/2 - len/2;
		return s.substr(index, len);
	}
```
####时间复杂度
每次如果p[j] < mx - i则肯定能在O(1)就算出p[i], 因为那个while循环只会执行一次.

每次如果p[j] > mx - i则发生右移mx的情形, 整个算法中mx最大值为2*n+1.

所以总的时间复杂度为O(n)
