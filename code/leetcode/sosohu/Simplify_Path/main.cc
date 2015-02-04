#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;


class Solution {

public:

	vector<string> split(string& str){
		vector<string> data;
		int len = str.length();
		int i = 0;
		while(str[i] == '/'){
			i++;
		}
		int start, end;
		while(i < len){
			start = i;
			while(i < len && str[i] != '/'){
				i++;
			}
			data.push_back(str.substr(start, i - start));
			while(i < len && str[i] == '/'){
				i++;
			}
		}
		return data;
	}

	string simplifyPath_1st(string path) {
		stack<string> s, tmp;
		vector<string> data = split(path);
		for(int i = 0; i < data.size(); i++){
			if(data[i].compare(".") == 0)
				continue;
			if(data[i].compare("..") == 0){
				if(!s.empty()){
					s.pop();
				}
				continue;
			}
			s.push(data[i]);
		}
		while(!s.empty()){
			tmp.push(s.top());
			s.pop();
		}
		if(tmp.empty()) return "/";
		string ret;
		while(!tmp.empty()){
			ret = ret + "/";
			ret = ret + tmp.top();
			tmp.pop();
		}
		return ret;
    }

	string simplifyPath(string path) {
		stack<string> s;
		string ret;
		int len = path.length();
		int i = 0;
		while(i < len && path[i] == '/')	i++;
		if(i == len)	return "/";
		while(i < len){
			string cur;
			while(i < len && path[i] != '/'){
				cur = cur + path[i++];
			}
			if(cur.compare("..") == 0){
				if(!s.empty())	s.pop();
			}else{
				if(cur.compare(".") != 0)
					s.push(cur);
			}
			while(i < len && path[i] == '/')	i++;
		}
		stack<string> bt;
		while(!s.empty()){
			string cur = s.top();
			s.pop();
			bt.push(cur);
		}
		while(!bt.empty()){
			string cur = bt.top();
			bt.pop();
			ret = ret + "/" + cur;
		}
		if(ret.length() == 0)	ret = "/";
		return ret;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	string s("/.../");		
	string ret = sl.simplifyPath(s);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
