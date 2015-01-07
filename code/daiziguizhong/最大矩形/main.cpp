#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	int maxRec(vector<vector<char> > &matrix) {
		if(0 == matrix.size())
			return 0;
		int m, n, i, j, k;
		int r_max = 0;
		m = matrix.size();
		n = matrix[0].size();
		vector<vector<int> > a(m, vector<int>(n,0));
		for(i = 0; i < m; i++) {
			for(j = 0; j < n; j++) {
				if(0 == i) {
					a[i][j] = matrix[i][j] - '0';
					continue;
				}
				a[i][j] = a[i - 1][j] && ('1' == matrix[i][j]) ? a[i - 1][j] + 1 : matrix[i][j] - '0'; 
			}
		}
		vector<pair<int, int> > stack;
		for(i = 0; i < m; i++) {
			stack.push_back(make_pair(0, a[i][0]));
			for(j = 1; j < n; j++) {
				if(a[i][j] > stack[stack.size() - 1].second) {
					stack.push_back(make_pair(j, a[i][j]));
				}
				else if(a[i][j] < stack[stack.size() - 1].second) {
					while(stack[stack.size() - 1].second > a[i][j] && !stack.empty()) {
						r_max = r_max > (j - stack[stack.size() - 1].first) * stack[stack.size() - 1].second ? r_max :
								(j - stack[stack.size() - 1].first) * stack[stack.size() - 1].second;
						k = stack[stack.size() - 1].first;
						stack.pop_back();
					}
					stack.push_back(make_pair(k, a[i][j]));
				}
			}
			while(!stack.empty()) {
				r_max = r_max > (j - stack[stack.size() - 1].first) * stack[stack.size() - 1].second ? r_max :
						(j - stack[stack.size() - 1].first) * stack[stack.size() - 1].second;
				stack.pop_back();
			}
		}
		return r_max;
	}
};
int main() {
	vector<vector<char> > a(5, vector<char>(5, '0'));
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			int k = 0;
			cin >> k;
			a[i][j] = k + '0';
		}
	}
	cout << (new Solution)->maxRec(a) << endl;
	return 0;
}
