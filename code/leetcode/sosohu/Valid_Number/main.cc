#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;


class Solution {

public:

	bool isNumber_1st(const char *s) {
		int len = strlen(s);	
		vector<int> marke, mark_add, mark_minus, mark_point;
		int pos , start, end;
		pos = 0;
		while(pos < len){
			if(s[pos] != ' ')	
				break;
			pos++;
		}
		if(pos == len)	return false;
		start = pos;
		pos = len - 1;
		while(pos >= 0){
			if(s[pos] != ' ')	
				break;
			pos--;
		}
		end = pos;
		for(pos = start; pos <= end; pos++){
			switch(s[pos]){
				case 'e': marke.push_back(pos); break; 
				case '+': mark_add.push_back(pos); break; 
				case '-': mark_minus.push_back(pos); break; 
				case '.': mark_point.push_back(pos); break; 
				default:	if(!(s[pos] <= '9' && s[pos] >= '0'))
							return false;
			}
		}
		if(mark_point.size() > 1)	return false;
		if(mark_add.size() + mark_minus.size() > 2)	return false;
		if(marke.size() > 1)	return false;

		if(marke.size() == 1){
			if(marke[0] == start || marke[0] == end) return false;
			//if(s[marke[0] - 1] > '9' || s[marke[0] - 1] < '0' )	return false;
			//if(s[marke[0] + 1] > '9' || s[marke[0] + 1] < '0' )	return false;
			//if(mark_point.size() && mark_point[0] == start) return false;
			//if(mark_point.size() && mark_point[0] == marke[0] - 1) return false;
			//if(mark_point.size() && mark_point[0] == marke[0] + 1) return false;
			//if(mark_point.size() && mark_point[0] == end) return false;
			if(mark_point.size() == 1 && mark_point[0] == start &&
				start == marke[0] - 1){
				return false;
			}
			if(mark_point.size() == 1 && mark_point[0] <= end &&
				mark_point[0] >= marke[0] + 1){
				return false;
			}
			if(mark_add.size() + mark_minus.size() == 2){
				if(s[start] != '+' && s[start] != '-')	return false;
				if(s[marke[0] + 1] != '+' && s[marke[0]+1] != '-')	return false;
				if(start + 1 == marke[0])	return false;
				if(end - 1 == marke[0])	return false;
			}
			if(mark_add.size() + mark_minus.size() == 1){
				if((s[start] != '+' && s[start] != '-')
					&& (s[marke[0] + 1] != '+' && s[marke[0]+1] != '-'))
					return false;

				if((s[start] == '+' || s[start] == '-') && start + 1 == marke[0])
					return false;
				if((s[marke[0]+1] == '+' || s[marke[0]+1] == '-') && end - 1 == marke[0])
					return false;
			}
		}else{
			if(mark_add.size() + mark_minus.size() > 1)	return false;
			if(mark_add.size() && mark_add[0] != start)	return false;
			if(mark_point.size() > 1)	return false;
			if(mark_point.size() == 1 && start == end){
				return false;
			}
			if(mark_minus.size() && mark_minus[0] != start)	return false;
			if(end - start + 1 == mark_add.size() + mark_minus.size() + mark_point.size())
				return false;
			//if(mark_point.size() && mark_point[0] == start) return false;
			//if(mark_point.size() && mark_point[0] == end) return false;
		}
		return true;
    }

	bool isNum(const char s){
		return s <= '9' && s >= '0';
	}

	bool isNumber_2nd(const char *s) {
		int state = 0;
		if(!s)	return false;
		while(*s){
			switch(state){
				case 0: {
							switch(*s){
								case ' ': break;	
								case '-': 	
								case '+': state = 1; break;	
								case '.': state = 3; break;	
								default:  if(isNum(*s))	state = 2;
										  else return false;
							}
							break;
						}
				case 1:	{
							switch(*s){
								case '.': state = 3; break;	
								default:  if(isNum(*s))	state = 2;
										  else return false;
							}
							break;
						}
				case 2: {
							switch(*s){
								case ' ': state = 8; break;	
								case '.': state = 4; break;	
								case 'e': state = 5; break;	
								default:  if(!isNum(*s)) return false;
							}
							break;
						}
				case 3: {
							if(isNum(*s)) state = 4;
							else return false;
							break;
						}
				case 4: {
							switch(*s){
								case ' ': state = 8; break;	
								case 'e': state = 5; break;	
								default:  if(!isNum(*s)) return false;
							}
							break;
						}
				case 5: {
							switch(*s){
								case '+': ;
								case '-': state = 6; break;
								default:  if(isNum(*s)) state = 7;
										  else return false;
							}
							break;
						}
				case 6: {
							if(isNum(*s)) state = 7;
							else return false;
							break;
						}
				case 7: {
							switch(*s){
								case ' ': state = 8; break;
								default:  if(!isNum(*s)) return false;
							}
							break;
						}
				case 8: {
							if(*s != ' ') return false;
							break;
						}
			}
			s++;
		}
		if(state == 8 || state == 4 || state == 7 || state == 2)
			return true;
		return false;
	}

	enum lexical{ valid, space, sign, number, dot, e };

	int isType(const char c){
		switch(c){
			case ' ': return 1;
			case '+': ;
			case '-': return 2;
			case '.': return 4;
			case 'e': return 5;
			default: if(c <= '9' && c >= '0')	return 3;
					 else return 0;
		}
	}

	bool isNumber(const char *s) {
		if(!s)	return false;
		//状态转移矩阵, -1表示非法
		int map[9][6] = {
			-1, 0, 1, 2, 3, -1,  // 0状态的转移
			-1, -1, -1, 2, 3, -1,
			-1, 8, -1, 2, 4, 5,
			-1, -1, -1, 4, -1, -1,
			-1, 8, -1, 4, -1, 5,
			-1, -1, 6, 7, -1, -1,
			-1, -1, -1, 7, -1, -1,
			-1, 8, -1, 7, -1, -1,
			-1, 8, -1, -1, -1, -1 
		};
		int state = 0;
		while(*s){
			state = map[state][isType(*s)];
			if(state == -1)	return false;
			s++;
		}
		return state == 2 || state == 4 || state == 7 || state == 8;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	const char* s = "-.3";		
	bool ret = sl.isNumber(s);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
