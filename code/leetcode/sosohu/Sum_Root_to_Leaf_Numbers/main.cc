#include <iostream>
#include <string>
#include <stdlib.h>

#define DATASIZE 6

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {

public:

	void sumNumbers_Detail(TreeNode* root, int& sum)
	{
		TreeNode* pos = root;
		int val = pos->val;
		sum =  sum*10 + val;
		
		if(pos->left == NULL && pos->right == NULL)
			return;

		int left_sum = sum;
		int right_sum = sum;
		sum = 0;
		if(pos->left){
			sumNumbers_Detail(pos->left, left_sum);
			sum = sum + left_sum;
		}
		if(pos->right){
			sumNumbers_Detail(pos->right, right_sum);
			sum = sum + right_sum;
		}
		return;
	}

	int sumNumbers_1st(TreeNode *root) {
		int sum = 0;
		sumNumbers_Detail(root, sum);
		return sum;
    }

	void dfs(TreeNode *root, int track, int &sum){
		if(!root)	return;
		track = track*10 + root->val;
		if(!root->left && !root->right){
			sum = sum + track;
		}
		if(root->left)
			dfs(root->left, track, sum);
		if(root->right)
			dfs(root->right, track, sum);
	}

	int sumNumbers(TreeNode *root) {
		int sum = 0;
		int track = 0;
		dfs(root, track, sum);
		return sum;
	}

};

int main(int argc, char** argv)
{
	Solution sl;

	TreeNode* root = (TreeNode*)malloc(DATASIZE*sizeof(TreeNode));
	int count = 0;
	while(count < DATASIZE){
		root[count].val = count + 1;
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


    int ret = sl.sumNumbers(root);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
