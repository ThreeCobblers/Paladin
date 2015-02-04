#include <iostream>
#include <string>
#include <climits>

using namespace std;


class Solution {

public:

	int atoi_1st(const char *str) {
		const char *p = str;
		bool has_sign = false;
		bool minis = false;
		int sum = 0;
		int IN_MAX = 2147483647;
		int IN_MIN = -2147483648; 
		while(*p != '\0' && *p != '+' && *p != '-' && (*p < '0' || *p > '9')){
		    if(*p != ' ')   return sum;
			p++;
		}
		if(*p == '\0')	return 0;
		while(*p != '\0'){
			if(*p == '+'){
				if(has_sign)	return false;
				has_sign = true;
				p++;
				continue;
			}
			if(*p == '-'){
				if(has_sign)	return false;
				has_sign = true;
				minis = true;
				p++;
				continue;
			}
			if(*p != '\0' && *p != '+' && *p != '-' && (*p < '0' || *p > '9')){
				break;
			}
			// judge the overflow
			if(sum > 214748364){
				if(minis)
					return IN_MIN;
				else
					return IN_MAX;
			}
			if(minis && sum == 214748364){
				if(*p == '9')	return IN_MIN;
				if(*p == '8')	return IN_MIN;
			}
			if(!minis && sum == 214748364){
				if(*p == '9' || *p == '8')	return IN_MAX;
			}
			sum = sum * 10 + ((*p) - '0');
			p++;
			//if(*p == '\0')	return sum;
		}
		if(minis)	sum = -sum;
		return sum;
    }
	
int atoi(const char *str){
	int sum = 0;  // 存负值.
	bool isMinus = false;
	const char* p = str;
	if(!p)	return 0;
	while(*p == ' ' && *p != '\0') p++; //空格
	if(*p == '\0')	return 0;
	if(*p == '-'){
		isMinus = true;
		p++;
	}else{
		if(*p == '+') p++;
	}
	while(*p != '\0'){
		int cur = *p++ - '0';
		if(!(cur >= 0 && cur <= 9))	break;  //非法字符
		if(isMinus && sum == INT_MIN/10 && cur > INT_MAX%10 + 1){
			return INT_MIN;
		}
		if(isMinus && sum < INT_MIN/10){
			return INT_MIN;
		}
		if(!isMinus && sum == -INT_MAX/10 && cur > INT_MAX%10){
			return INT_MAX;
		}
		if(!isMinus && sum < -INT_MAX/10){
			return INT_MAX;
		}
		sum = sum*10 - cur;
	}
	if(!isMinus)	return -sum;
	return sum;
}

};

int main(int argc, char** argv)
{
	Solution sl;
	const char *s = "  -0012a42";		
	int ret = sl.atoi(s);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
