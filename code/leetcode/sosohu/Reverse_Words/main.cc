#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class Solution {

public:

    void reverseWords_1st(string &s) {
        int len = s.length();
		if(len == 0)
			return;

		int mid = -1;
		for(int i = len / 2, j = len / 2; i >= 0 || j <= len -1; i--, j++ ){
			if(i >= 0 && s[i] == ' '){
					mid = i;
					break;
			}
			if(j <= len - 1 && s[j] == ' '){
					mid = j;
					break;
			}
		}

		if(mid == -1)
			return;

		string down(s, mid + 1, len - mid - 1);
		string up(s, 0,  mid);
		reverseWords(down);
		reverseWords(up);

		s.replace(0,len - mid - 1, down, 0, len - mid -1);
		s.replace(len - mid, mid, up, 0, mid);
		
		s[len - mid -1] = ' ';
    }

    void reverseWords(string &s) {
		reverse(s.begin(), s.end());
		int i = 0, last;
		string str, word;
		while(i < s.length()){
			while(i < s.length() && s[i] == ' ') i++;
			if(i == s.length()) break;
			last = i;
			while(i < s.length() && s[i] != ' ') i++;
			word = s.substr(last, i - last);
			reverse(word.begin(), word.end());
			str = str + word + " ";
		}
		if(!str.empty())
			s.assign(str.begin(), str.end() - 1);
		else
			s = str;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	string s("   ");		
    sl.reverseWords(s);
	
	cout<<"Result  :("<<s<<")"<<endl;

	return 0;

}
