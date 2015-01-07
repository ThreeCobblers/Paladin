#include <iostream>
#include <vector>
#include <climits>
#include <cstdio>

using namespace std;

int getMinSpanningTree(vector<vector<int> > &data, int n){
	if(n <= 0)	return 0;
	vector<int> closeEdge(n, 0);
	// 初始化closeEdge函数
	for(int i = 1; i < n; i++){
		closeEdge[i] = data[0][i];
	}
	int sum = 0, count = 1, min = 0, index = 0;
	while(count++ < n){
		min = INT_MAX;
		for(int i = 0; i < n; i++){
			if(closeEdge[i] != 0 && min > closeEdge[i]){
				index = i;
				min = closeEdge[i];
			}
		}
		sum = sum + min;
		closeEdge[index] = 0; // 不用再被找
		for(int i = 0; i < n; i++){
			if(closeEdge[i] != 0 && data[index][i] < closeEdge[i])
				closeEdge[i] = data[index][i];
		}
	}
	return sum;
}


int main(int argc, char** argv)
{
	#ifdef DEBUG
	freopen("input", "r", stdin);
	#endif
	int n;
	cin>>n;
	vector<vector<int> > data(n, vector<int>(n, 0));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin>>data[i][j];
		}
	}
	int ret = getMinSpanningTree(data, n);
	cout<<ret<<endl;
	return 0;
}
