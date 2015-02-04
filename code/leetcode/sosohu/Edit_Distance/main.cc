#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;


class Solution {

public:

	int minDistance_1st(string word1, string word2) {	
		int len1 = word1.length();
		int len2 = word2.length();
		vector<vector<int> > data(len1+1, vector<int>(len2+1, 0));

		for(int i = 0; i < len1 + 1; i++)
			data[i][0] = i;
		for(int j = 0; j < len2 + 1; j++)
			data[0][j] = j;

		for(int i = 1; i < len1 + 1; i++){
			for(int j = 1; j < len2 + 1; j++){
				if(word1[i - 1] == word2[j - 1])
					data[i][j] = data[i-1][j-1];
				else{
					data[i][j] = data[i-1][j] < data[i][j-1]? data[i-1][j]:data[i][j-1];
					if(data[i][j] > data[i-1][j-1])
						data[i][j] = data[i-1][j-1];
					data[i][j]++;
				}
			}
		}
		return data[len1][len2];
    }

	int minDistance(string word1, string word2) {	
		int l1 = word1.length(), l2 = word2.length();
		vector<vector<int> > d(l1+1, vector<int>(l2+1, 0));
		for(int i = 0; i < l1 + 1; i++)	d[i][0] = i;
		for(int j = 0; j < l2 + 1; j++)	d[0][j] = j;
		
		for(int i = 1; i < l1 + 1; i++){
			for(int j = 1; j < l2 + 1; j++){
				if(word1[i-1] == word2[j-1])	d[i][j] = d[i-1][j-1];
				else	d[i][j] = d[i-1][j-1] + 1;
				d[i][j] = min(d[i][j], d[i-1][j] + 1);
				d[i][j] = min(d[i][j], d[i][j-1] + 1);
			}
		}

		return d[l1][l2];
	}
};

int main(int argc, char** argv)
{
	Solution sl;
	string s1("catk"), s2("attk");
	int ret = sl.minDistance(s1, s2);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
