#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

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

	vector<vector<int> > pathSum_1st(TreeNode *root, int sum){
		vector<vector<int> > tmp = detail(root, sum);
		vector<vector<int> > ret = tmp;
		for(int i = 0; i < tmp.size(); i++){
			for(int j = tmp[i].size() - 1, k = 0; j >= 0; j--, k++){
				ret[i][k] = tmp[i][j];
			}
		}
		return ret;
	}

	vector<vector<int> > detail(TreeNode *root, int sum){
		vector<vector<int> > ret;
		if(root == NULL)
			return ret;
		int val = root->val;
		sum = sum - val;
		if(sum == 0 && !root->left && !root->right){
			vector<int> vec;
			vec.push_back(val);
			ret.push_back(vec);
			return ret;
		}

		vector<vector<int> > left , right;
		if(root->left){
			left = detail(root->left, sum);	
		}
		if(root->right)
			right =  detail(root->right, sum);

		for(int i = 0; i < left.size(); i++){
			left[i].push_back(val);
			ret.push_back(left[i]);
		}
		for(int i = 0; i < right.size(); i++){
			right[i].push_back(val);
			ret.push_back(right[i]);
		}
		return ret;
	}

	vector<vector<int> > pathSum(TreeNode *root, int sum){
		vector<int> cur;
		vector<vector<int> > result;
		recursion(root, cur, result, sum);
		return result;
	}

	void recursion(TreeNode *root, vector<int> &cur, vector<vector<int> > &result, int sum){
		if(!root)	return;
		cur.push_back(root->val);
		if(!root->left && !root->right && root->val == sum)
			result.push_back(cur);
		if(root->left)
			recursion(root->left, cur, result, sum - root->val);
		if(root->right)
			recursion(root->right, cur, result, sum - root->val);
		cur.pop_back();
	}
};

int main(int argc, char** argv)
{
	Solution sl;
	
	TreeNode* root = (TreeNode*)malloc(DATASIZE*sizeof(TreeNode));
	int count = 0;
	while(count < DATASIZE){
		root[count].val = count;
		if(2*count + 1 < DATASIZE){
			root[count].left = &root[2*count + 1]; 
		}
		else{
			root[count].left = NULL; 
		}
		if(2*count + 2 < DATASIZE){
			root[count].right = &root[2*count + 2]; 
		}
		else{
			root[count].right = NULL; 
		}
		count++;
	}	
	root[4] = 6;
	
	vector<vector<int> > ret = sl.pathSum(root, 7);
	
	for(int i = 0; i < ret.size(); i++){
		for(int j = 0; j < ret[i].size(); j++)
			cout<<ret[i][j]<<" ";
		cout<<endl;
	}

	return 0;

}
