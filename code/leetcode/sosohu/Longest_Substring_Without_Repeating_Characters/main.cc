#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


class Solution {

public:

	int lengthOfLongestSubstring_1st(string s) {
		vector<int> appear = vector<int>(256, -1);
		int len = s.length();
		if(len == 0)	return 0;
		appear[s[0]] = 0;
		int max = 1, next = 1;
		int next_first = 0;
		for(int i = 1; i < len; i++){
			if(appear[s[i]] != -1){
				if(appear[s[i]] >= next_first){
					next_first = appear[s[i]] + 1;
					next = i - appear[s[i]];
				}else{
					next++;
				}
				appear[s[i]] = i;
			}else{
				appear[s[i]] = i;
				next++;
			}
			if(next > max){
				max = next;
			}
		}
		return max;
    }

	int lengthOfLongestSubstring(string s) {
		vector<bool> appear(256, false);
		int ret = 0, con = 0;
		for(int i = 0; i < s.length(); i++){
			if(!appear[s[i]]){
				con++;
				appear[s[i]] = true;
				ret = max(ret, con);
			}else{
				for(int j = i - con; j < i && s[j] != s[i]; j++){
					appear[s[j]] = false;
					con--;
				}
			}
		}
		return ret;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	string s("ruowzgiooobpple");		
    int ret = sl.lengthOfLongestSubstring(s);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
