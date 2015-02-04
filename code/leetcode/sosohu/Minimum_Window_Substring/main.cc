#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;


class Solution {

public:

	string minWindow_1st(string S, string T) {
		int expect[256] = {0};
		int appear[256] = {0};
		int sl = S.length(); 
		int tl = T.length();
		if(tl == 0)	return "";
		if(sl < tl) return "";

		for(int i = 0; i < tl; i++)
			expect[T[i]]++;	

		int min = sl + 1;
		int start = 0, win_start = 0, win_end = 0, appear_size = 0, pos = 0;
		
		for(; pos < sl; pos++){
			if(expect[S[pos]] > 0){
				appear[S[pos]]++ ;
				if(appear[S[pos]] <= expect[S[pos]])
					appear_size++;
			}	
			if(appear_size == tl){
				while(expect[S[start]] < appear[S[start]] 
						|| expect[S[start]] == 0){
					if(expect[S[start]])
						appear[S[start]]--;
					start++;	
				}
				if(min > pos - start){
					min = pos - start;
					win_start = start;
					win_end = pos;
				}
			}
		}
		if(min  == sl + 1)	return "";
		return S.substr(win_start, win_end - win_start + 1);
    }

	string minWindow(string S, string T) {
		vector<int> table(256, 0);
		vector<int> apper(256, 0);
		for(int i = 0; i < T.length(); i++) table[T[i]]++;
		int len = INT_MAX, num = 0, last = 0, pos = 0;
		for(int i = 0; i < S.length(); i++){
			apper[S[i]]++;
			if(apper[S[i]] <= table[S[i]]) num++;
			while(apper[S[last]] > table[S[last]]){
				apper[S[last]]--;
				last++;
			}
			if(num == T.length() && len > i - last + 1){
				len = i - last + 1;
				pos = last;
			}
		}
		return num == T.length()? S.substr(pos, len) : "";
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	string S("cabwefgewcwaefgcf"), T("cae");
    string ret = sl.minWindow(S, T);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
