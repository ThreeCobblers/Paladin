#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;


class Solution {

public:

	string longestCommonPrefix_1st(vector<string> &strs) {
		int size = strs.size();
		string str;
		if(size == 0)	return str;
		bool done = false;
		vector<int>	pos(size, 0);
		vector<int>	length(size, 0);
		for(int i = 0; i < size; i++){
			length[i] = strs[i].length();
		}
		int count = 0;
		while(1){
			for(int i = 0; i < size; i++){
				if(pos[i]++ == length[i]){
					done = true;
					break;
				}
			}
			if(done)	break;
			char cur = strs[0][count];
			for(int i = 1; i < size; i++){
				if(strs[i][count] != cur){
					done = true;
					break;
				}
			}	
			if(done)	break;
			count++;
		}
		str = strs[0].substr(0, count);
		return str;
    }

	string longestCommonPrefix(vector<string> &strs) {
		string ret;
		if(strs.size() == 0)	return ret;
		int len = INT_MAX;
		for(int i = 0; i < strs.size(); i++)
			if(len > strs[i].length())	len = strs[i].length();
		for(int j = 0; j < len; j++){
			for(int i = 1; i < strs.size(); i++)
				if(strs[i][j] != strs[i-1][j])	return ret;
			ret.push_back(strs[0][j]);
		}
		return ret;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	vector<string> data{"abca", "abc"};
	string ret = sl.longestCommonPrefix(data);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
