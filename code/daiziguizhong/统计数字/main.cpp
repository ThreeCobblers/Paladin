/*Count number

There is a array contions numbers between 1 to n, some numbers may appear many times, but some may not appear
can you write a programs that count which number appear and how many time it does with O(n) time and constant 
space.
*/

#include <iostream>
using namespace std;

class Solution {
public:
	void countNum(int a[], int n) {
		if(0 == n)
			return;
		for(i = 0; i < n; i++) {a[i] = a[i] * n;}
		for(i = 0; i < n; i++) {a[a[i]/n]++;}
		for(i = 0; i < n; i++) {a[i] = a[i] % n;}
	}
};