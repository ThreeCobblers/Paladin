#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

#define DATASIZE 7

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {

public:
	/* 1st
	vector<TreeNode* > generate(int start, int end){

		vector<TreeNode*> data;
		if(start > end){
			data.push_back(NULL);
			return data;
		}
		
		vector<TreeNode*> left, right;
		
		for(int i = start; i <= end; i++){
			left = generate(start, i-1);
			right = generate(i+1, end);
			for(int j = 0; j < left.size(); j++){
				for(int k = 0; k < right.size(); k++){
					TreeNode* father = new TreeNode(i);
					father->left = left[j];
					father->right = right[k];
					data.push_back(father);
				}
			}
		}
		return data;
	}

	vector<TreeNode*> generateTrees(int n) {
		if(n == 0){
			vector<TreeNode*> data;
			data.push_back(NULL);
			return data;
		}
		return generate(1, n);
    }
	*/

	vector<TreeNode*> generate(int start, int end){
		if(start == end){
			return vector<TreeNode*>(1, new TreeNode(start));
		}
		vector<TreeNode*> data;
		if(start > end){
			data.push_back(NULL);
			return data;
		}
		for(int i = start; i <= end; i++){
			TreeNode* root;
			vector<TreeNode*> left = generate(start, i - 1);
			vector<TreeNode*> right = generate(i + 1, end);
			for(int j = 0; j < left.size(); j++){
				for(int k = 0; k < right.size(); k++){
					root = new TreeNode(i);
					root->left = left[j];
					root->right = right[k];
					data.push_back(root);
				}
			}
		}
		return data;
	}

	vector<TreeNode*> generateTrees(int n) {
		return generate(1, n);
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	
	vector<TreeNode*> ret = sl.generateTrees(3);
	
	cout<<"size: "<<ret.size()<<endl;

	return 0;

}
