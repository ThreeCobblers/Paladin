#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Solution {

public:

	bool isMatch_1st(const char *s, const char *p) {
		#ifdef DEBUG
		cout<<*s<<" "<<*p<<endl;
		#endif
		if(*s == '\0' && *p == '\0')
			return true;
		if(*p == '\0')
			return false;
		if(*s == '\0'){
			while(*p != '\0' && *(p+1) == '*'){
				p++;
				p++;
			}
			if(*p == '\0')
				return true;
			else
				return false;
		}
		const char *ps, *pp;
		ps = s;
		pp = p;
		int ret = false;
		if(*p == '.'){
			if(*(p+1) == '*'){
				ret = ret | isMatch(s, p+2);
				s++;
				ps = s;
				while(*ps != '\0'){
					ret = ret | isMatch(ps, p+2);
					ps++;
				}
				if(*ps == '\0' && *(p+2) == '\0')	return true;
				ret = ret | isMatch(ps, p+2);
				return ret;
			}else{
				return isMatch(++s, ++p);
			}
		}
		// default not . or *
		if(*s == *p){
			if(*(p+1) == '*'){
				ps = s;
				while(*ps != '\0' && *ps == *s){
					ret = ret | isMatch(ps, p+2);
					ps++;
				}
				if(*ps == '\0' && *(p+2) == '\0')	return true;
				ret = ret | isMatch(ps, p+2);
				return ret;
			}else{
				return isMatch(++s, ++p);
			}	
		}else{
			if(*(p+1) == '*'){
				return isMatch(s, p+2);
			}else
				return false;
		}
    }

	//递归做法
	bool isMatch_2nd(const char *s, const char *p) {
		switch(*s){
			case '\0': 	if(*p == '\0')	return true;
						if(*p == '*')	return false;
						if(*(p+1) != '*')	return false;
						p++;
						while(*p != '\0' && *p == '*')	p++;
						if(*p != '\0')	return isMatch(s, p);
						return true;
			default:	if(*p == '\0')	return false;
						if(*(p+1) != '*'){
							if(*s == *p || *p == '.')	return isMatch(++s, ++p);
							else	return false;
						}else{
							const char* cur = p;
							p++;
							while(*p != '\0' && *p == '*')	p++;
							if(isMatch(s, p))	return true;
							if(*s == *cur || *cur == '.') 	return isMatch(++s, cur);
							else	return false;
						}
		}
	}

	//动态规划
	bool isMatch(const char *s, const char *p) {
		int ls = strlen(s);
		int lp = strlen(p);
		vector<vector<bool> > isMatch(ls+1, vector<bool>(lp+1, false));
		isMatch[0][0] = true;
		int di, dj;
		for(int i = 0; i < ls + 1; i++){ // 注意起始坐标
			di = i - 1;
			for(int j = 1; j < lp + 1; j++){ // 注意起始坐标
				dj = j - 1;
				if(p[dj] != '*'){
					isMatch[i][j] = di != -1 && isMatch[i-1][j-1] && (s[di] == p[dj] || p[dj] == '.');
				}else{
					if(dj == 0) { isMatch[i][j] = false; continue; }
					if(p[dj-1] == '.'){
							isMatch[i][j] = isMatch[i][j-2] || (di != -1 && isMatch[i-1][j]);
					}else{
						if(p[dj-1] == '*')	isMatch[i][j] = isMatch[i][j-1];	
						else isMatch[i][j] = isMatch[i][j-2] || (di != -1 && s[di] == p[dj-1] && isMatch[i-1][j]);
					}
				}
			}
		}
		return isMatch[ls][lp];
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	const char *s1 = "aasdfasdfasdfasdfas";		
	const char *s2 = "aasdf.*asdf.*asdf.*asdf.*s";
    int ret = sl.isMatch(s1, s2);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
