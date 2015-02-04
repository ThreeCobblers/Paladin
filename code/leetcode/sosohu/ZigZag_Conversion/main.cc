#include <iostream>
#include <string>

using namespace std;


class Solution {

public:

	string convert_1st(string s, int nRows) {
		int size = s.length();
		string str;
		if(size == 0)	return str;
		if(nRows == 1)	return s;
		int pos = 0;
		while(pos < size){
			str = str + s[pos];
			pos = pos + 2*(nRows - 1);
		}
		for(int i = 1; i < nRows - 1; i++){
			pos = i;
			while(pos < size){
				str = str + s[pos];
				pos = pos + 2*(nRows - 1 - i);
				if(pos < size){
					str = str + s[pos];
					pos = pos + 2*i;
				}else{
					break;
				}
			}
		}	
		pos = nRows - 1;
		while(pos < size){
			str = str + s[pos];
			pos = pos + 2*(nRows - 1);
		}
		return str;
    }

	string convert(string s, int nRows) {
		if(nRows == 1)	return s;
		int len = s.length();
		string ret;
		for(int i = 0; i < nRows; i++){
			int start = i, gap = nRows - i - 1;
			while(start < len){
				ret.push_back(s[start]);
				if(!gap) gap = nRows - 1 - gap;
				start = start + 2*gap;
				gap = nRows - 1 - gap;
			}
		}
		return ret;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	string s("PAYPALISHIRING");		

	string ret = sl.convert(s, 3);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
