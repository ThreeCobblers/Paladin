#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class Solution {

public:

	string addBinary_1st(string a, string b) {
		int la = a.length();
		int lb = b.length();
		string ret;
		if(la * lb == 0)
			return ret;
		if(la < lb){
			string tmp = a;
			a = b;
			b = tmp;
			la = la + lb;
			lb = la - lb;
			la = la - lb;
		}
		int ia, ib, sum;
		int carry = 0;
		for(int i = 0; i < la; i++){
			ia = 0;
			ib = 0;
			if(a[la - 1 - i] == '1')
				ia = 1;
			if(i < lb){
				if(b[lb - 1 - i] == '1')
					ib = 1;
			}
			sum = ia + ib + carry;
			switch(sum){
				case 0: ret = ret + "0"; carry = 0; break;
				case 1: ret = ret + "1"; carry = 0; break;
				case 2: ret = ret + "0"; carry = 1; break;
				case 3: ret = ret + "1"; carry = 1; break;
				default: ;
			}
		}
		if(carry)
			ret = ret + "1";
		reverse(ret.begin(), ret.end());
		return ret;
    }

	string addBinary(string a, string b) {
		int la = a.length(), lb = b.length();
		int carry = 0, sum = 0;
		string ret;
		while(la || lb || carry){
			sum = carry + (la > 0? a[la-1] - '0' : 0) + (lb > 0? b[lb-1] - '0' : 0);
			ret.push_back(sum%2 + '0');
			carry = sum/2;
			if(la)	la--;
			if(lb)	lb--;
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	string a("1101"), b("111");
	
	string ret = sl.addBinary(a, b);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
