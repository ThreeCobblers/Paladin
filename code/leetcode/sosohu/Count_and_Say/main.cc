#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {

public:

	string countAndSay_1st(int n) {
		if(n == 0)	return "";
		vector<int> last;
		vector<int> cur;
		last.push_back(1);
		for(int i = 1; i < n; i++){
			cur.clear();
			int pos = 1;
			int last_one = last[0];
			int count_one = 1;
			while(pos < last.size()){
				if(last[pos] != last_one){
					cur.push_back(count_one);
					cur.push_back(last_one);
					count_one = 1;
					last_one = last[pos];
				}else{
					count_one++;	
				}
				pos++;
			}
			cur.push_back(count_one);
			cur.push_back(last_one);
			last = cur;
		}
		
		string str;
		for(int i = 0; i < cur.size(); i++){
			switch(cur[i]){
				case 0: str = str + "0"; break;
				case 1: str = str + "1"; break;
				case 2: str = str + "2"; break;
				case 3: str = str + "3"; break;
				case 4: str = str + "4"; break;
				case 5: str = str + "5"; break;
				case 6: str = str + "6"; break;
				case 7: str = str + "7"; break;
				case 8: str = str + "8"; break;
				case 9: str = str + "9"; break;
				default: ;
			}
		}
		return str;
    }

	string parse(string& str){
		string ret;
		int last = 0, len = str.length();
		for(int i = 0; i < len; i++){
			last = i;
			while(i < len - 1 && str[i] == str[i+1])	i++;
			ret.push_back(i - last + 1 + '0');	
			ret.push_back(str[last]);	
		}
		return ret;
	}

	string countAndSay(int n) {
		string last = "1", cur;
		if(n < 1)	return cur;
		while(n-- > 1){
			last = cur = parse(last);
		}
		return last;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
    string ret = sl.countAndSay(5);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
