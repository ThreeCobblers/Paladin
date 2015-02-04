#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class Solution {

public:
	inline bool isAlpha(char c){
		if(c <= 'Z' && c >= 'A')
			return true;
		if(c <= 'z' && c >= 'a')
			return true;
		if(c <= '9' && c >= '0')
			return true;
		return false;
	}

	inline bool isequal(char lfs, char rhs){
		if(lfs == rhs || lfs - 32 == rhs || lfs == rhs - 32)	return true;
		return false;
	}

	bool isPalindrome_1st(string s) {
		string tmp;
		int size = s.size();
		if(size <= 1) return true;
		for(int i = 0, j = size - 1 ; i < size; i++, j--){
			while(!isAlpha(s[i])){
				i++;
				if(i > size - 1) return true;
			}
			while(!isAlpha(s[j])){
				j--;
				if(j < 0)  return true;
			}
			if(i >= j) return true;
			if(!isequal(s[i], s[j])) return false;
		}
    }

	bool isPalindrome(string s) {
		int len = s.length();
		int start = 0, end = len - 1;
		while(start < end){
			while(start < end && !isAlpha(s[start]))	start++;
			if(start == end)	return true;
			while(end > start && !isAlpha(s[end]))	end--;
			if(s[start] != s[end] && abs(s[start] - s[end]) != abs('a' - 'A')) return false;
			start++;
			end--;
		}
		return true;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	string s("Aa");		
    bool ret = sl.isPalindrome(s);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
