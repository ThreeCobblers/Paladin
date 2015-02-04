#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <climits>

using namespace std;


class Solution {

public:

	string longestPalindrome_1st(string const& s) {
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

	string longestPalindrome(string const& s) {
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

};

int main(int argc, char** argv)
{
	Solution sl;
	string s("aaaa");		
    string ret = sl.longestPalindrome(s);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
