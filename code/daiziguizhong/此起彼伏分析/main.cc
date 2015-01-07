#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

void findT(vector<int> &data, int s, int e, int t){
	if(s > e)	return;
	if(t == data[s]){
		cout<<s<<endl;
		findT(data, s + 1, e, t);
		return;
	}
	int gap = abs(t - data[s]);
	findT(data, s + gap, e, t);
}

int main(){
	int n;
	freopen("input", "r", stdin);
	cin>>n;
	vector<int> data(n, 0);
	for(int i = 0; i < n; i++)
		cin>>data[i];
	int t;
	cin>>t;
	findT(data, 0, n-1, t);
}
