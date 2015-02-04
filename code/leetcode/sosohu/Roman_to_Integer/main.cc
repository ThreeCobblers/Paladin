#include <iostream>
#include <string>

using namespace std;


class Solution {

public:

	int getNum(char c){
		switch(c){
			case 'I': return 1;
			case 'V': return 5;
			case 'X': return 10;
			case 'L': return 50;
			case 'C': return 100;
			case 'D': return 500;
			case 'M': return 1000;
			default: return 0;
		}
	}

	int romanToInt_1st(string s) {
		int len = s.length();
		int sum = 0, cur;
		int i = 0;
		int last = 0;
		while(i < len){
			#ifdef DEBUG
			cout<<sum<<endl;
			#endif
			cur = getNum(s[i]);
			if(i + 1 == len){	
				sum = sum + cur;
				break;
			}
			if(cur > getNum(s[i+1])){
				sum = sum + cur;
				i++;
				continue;
			}else{
				last = cur;
				while(i < len - 1 && cur == getNum(s[i+1])){
					last = last + cur;
					i++;
				}
				if(i == len - 1){
					sum = sum + last;
					i++;
				}else{
					if(cur < getNum(s[i+1]))
						sum = sum - last;
					else
						sum = sum + last;
					i++;
				}
			}
		}
		return sum;
    }

	int mapNum(char c){
		switch(c){
			case 'I': return 1;
			case 'V': return 5;
			case 'X': return 10;
			case 'L': return 50;
			case 'C': return 100;
			case 'D': return 500;
			case 'M': return 1000;
			default: return 0;
		}
	}

	int romanToInt(string s) {
		int len = s.length();
		int sum = 0;
		for(int i = 0; i < len; i++){
			if(i < len - 1 && mapNum(s[i]) < mapNum(s[i+1]))	sum -= mapNum(s[i]);
			else	sum += mapNum(s[i]);
		}
		return sum;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	string s("MDLXX");		
	int ret = sl.romanToInt(s);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
