#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {

public:

	int numTrees_1st(int n) {
		if(n == 0)	return 0;
		vector<int> num(n, 0);

		num[0] = 1;
		num[1] = 2;
		for(int i = 2; i < n; i++){
			num[i] = num[i-1];
			num[i] = num[i] + num[i-1];
			for(int j = 1; j < i; j++){
				num[i] = num[i] + num[j-1]*num[i - j -1];
			}
		}
		return num[n-1];	
    }

	int numTrees(int n) {
		if(!n)	return 0;
		vector<int> num(n+1, 0);
		num[1] = 1;
		num[2] = 2;
		for(int i = 3; i <= n; i++){
			num[i] = 2*num[i-1];
			for(int j = 1; j < i; j++){
				num[i] = num[i] + num[j]*num[i-1-j];
			}
		}
		return num[n];
	}
};

int main(int argc, char** argv)
{
	Solution sl;
    int ret = sl.numTrees(5);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
