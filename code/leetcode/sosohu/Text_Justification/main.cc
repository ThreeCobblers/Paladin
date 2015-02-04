#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {

public:

	vector<string> fullJustify_1st(vector<string> &words, int L) {
		int size = words.size();
		vector<string> data;

		int left = L, word_size, used, word_count, add, remain;
		vector<string> line;
		for(int i = 0; i < size; i++){
			word_size = words[i].size();
			if(left >= word_size){
				line.push_back(words[i]);
				used = used + word_size + 1;
				left = left - word_size - 1;
			}else{
				left++;
				word_count = line.size();
				if(word_count == 1){
					string line_str = line[0];
					string add_str(L - line_str.length(), ' ');
					line_str = line_str + add_str;
					data.push_back(line_str);
				}
				else{
					add = left / (word_count - 1);
					remain = left - (word_count - 1)* add;
					add = add + 1;
					string space1(add + 1, ' '), space2(add, ' ');
					string line_str;
					for(int j = 0; j < remain; j++){
						line_str = line_str + line[j] + space1;
					}
					for(int j = remain; j < word_count - 1; j++){
						line_str = line_str + line[j] + space2;
					}
					line_str = line_str + line[word_count - 1];
					data.push_back(line_str);
				}
				left = L;
				i--;
				line.clear();
			}
		}
		string line_str;
		for(int j = 0; j < line.size() - 1; j++){
			line_str = line_str + line[j] + " ";
		}
		line_str = line_str + line[line.size() - 1];
		string add_str(L - line_str.length(), ' ');
		line_str = line_str + add_str;
		
		data.push_back(line_str);
		return data;
    }

	vector<string> fullJustify(vector<string> &words, int L) {
		vector<string> ret;
		if(L < 1 || !words.size()){ 
			string str(L, ' ');
			ret.push_back(str);	
			return ret;
		}
		int last = 0, cur = 0, num = 0, left = 0;
		while(cur < words.size()){
			int sum = 0;
			last = cur;
			while(cur < words.size() && sum + words[cur].length() <= L){
				sum = sum + words[cur].length() + 1;
				cur++;
			}
			num = cur - last; // 词数
			sum = sum - num; // num个词总长
			left = L - sum; // 余下空格长度
			if(num == 1){
				string margin(left, ' ');
				words[last] = words[last] + margin;
				ret.push_back(words[last]);
				continue;
			}
			if(cur == words.size()){
				string line, s(1, ' ');
				for(int i = 0; i < num - 1; i++){
					line = line + words[last++] + s;
				}
				line = line + words[last++];
				string margin(left - num + 1, ' ');
				line = line + margin;
				ret.push_back(line);
				continue;
			}
			int gap = left / (num - 1);
			int remain = left % (num - 1);
			string line, s1(gap + (remain == 0? 0 : 1), ' '), s2(gap, ' ');
			for(int i = 0; i < remain; i++){
				line = line + words[last++] + s1;
			}
			for(int i = remain; i < num - 1; i++){
				line = line + words[last++] + s2;
			}
			line += words[last];
			ret.push_back(line);
		}
		return ret;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	vector<string> words(7, "");
	words[0] = "This";
	words[1] = "is";
	words[2] = "an";
	words[3] = "example";
	words[4] = "of";
	words[5] = "text";
	words[6] = "justification";

	vector<string> ret = sl.fullJustify(words, 16);
	
	for(int i = 0; i < ret.size(); i++)
		cout<<ret[i]<<endl;

	return 0;

}
