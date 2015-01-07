#include <iostream>
using namespace std;

class Solution {
public:
	int maxContion(int a[], int n, int L) {
		if(1 == n)
			return 1;
		int l = 0;
		int j = 0;
		int contion = 0;
		int max = INT_MIN;
		int count = 0;
		while(j < n) {
			while(j < n && a[j] - a[l] <= L) {j++; contion++; max = max > contion ? max : contion; count++;}
			l++;
			contion--;
			count++;
		}
		return max;
	}
};
int main() {
	int a[] = {1,2,3,4,15,16,17,18,25,26,27,28,29,30,31,32,33,34,35,36,39};
	Solution s;
	int res = 0;
	for(int i = 1; i < 39; i++)
		res += s.maxContion(a, 21, i);
	cout << res / 38.0 << endl;
	return 0;
}