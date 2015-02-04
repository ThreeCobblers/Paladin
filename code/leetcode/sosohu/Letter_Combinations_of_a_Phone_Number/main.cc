#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {

public:

	inline vector<string> get_str(char num){
		vector<string> data(3, " ");
		int number = num - '0';
		if(number < 7){
			for(int i = 0; i < 3; i++)
				data[i][0] = 'a' + (number - 2)*3 + i;
		}else{
			if(number == 7){
				data.push_back(" ");
				for(int i = 0; i < 4; i++)
					data[i][0] = 'a' + (number - 2)*3 + i;
			}
			if(number == 8){
				for(int i = 0; i < 3; i++)
					data[i][0] = 't' + i;
			}
			if(number == 9){
				data.push_back(" ");
				for(int i = 0; i < 4; i++)
					data[i][0] = 'w' + i;
			}
		}
		return data;		
	}

	void recursion(vector<string> &data, string &digits, int len, int pos){
		if(pos == -1){
			data.push_back(string(""));
			return;
		}
		recursion(data, digits, len , pos - 1);
		char num = digits[pos];
		vector<string> cur = get_str(num);
		int size = data.size();
		for(int i = 0; i < cur.size() - 1; i++){
			for(int j = 0; j < size; j++)
				data.push_back(data[j]);
		}
		for(int i = 0; i < size; i++){
			for(int j = 0; j < cur.size(); j++){
				data[i+j*size] += cur[j][0]; 
			}
		}
	}

	vector<string> letterCombinations_1st(string digits) {
		vector<string> data;
		int len = digits.length();
		if(len == 0){
			data.push_back("");
			return data;
		}
		recursion(data, digits, len, len-1);
		return data;
    }
	

	void recursion(vector<string> &result, string &digits, string map[], string& path, int end){
		if(end < 0){
			result.push_back(path);
			return;
		}
		int index = digits[end] - '0';
		string tmp = path;
		path = " " + path;
		for(int i = 0; i < map[index].length(); i++){
			path[0] = map[index][i];
			recursion(result, digits, map, path, end - 1);
		}
		path = tmp;
	}

	vector<string> letterCombinations(string digits) {
		int len = digits.length();
		vector<string> result;
		string map[] = {" ","", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
		string path;
		recursion(result, digits, map, path, len - 1);
		return result;
	}

};


int main(int argc, char** argv)
{
	Solution sl;
	string s("37");		
	vector<string> ret = sl.letterCombinations(s);
	
	for(int i = 0; i < ret.size(); i++)
		cout<<ret[i]<<endl;

	return 0;

}
