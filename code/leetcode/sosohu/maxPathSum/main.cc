#include <iostream>
#include <string>
#include <stdlib.h>
#include <climits>

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

	void detail(TreeNode* root, int& inside, int& outside){
		if(root == NULL){
			inside = 0;
			outside = 0;
			return;
		}
		int val = root->val;
		int left_inside, left_outside, right_inside, right_outside;
		detail(root->left, left_inside, left_outside);
		detail(root->right, right_inside, right_outside);

		if(left_outside < 0 && right_outside < 0){
			outside = val;
		}
		else{
			outside = left_outside > right_outside? left_outside : right_outside;
			outside = outside + val;
		}
		inside = val;
		if(left_outside > 0) inside = inside + left_outside;
		if(right_outside > 0) inside = inside + right_outside;

		if(inside < left_inside && left_inside != 0) inside = left_inside;
		if(inside < right_inside && right_inside != 0) inside = right_inside;
	}

	int maxPathSum_1st(TreeNode *root) {
		int inside, outside;
		detail(root, inside, outside);
		return inside;	
    }

	int dfs(TreeNode *root, int &result){
		if(!root)	return 0;
		if(!root->left && !root->right){
			if(result < root->val)
				result = root->val;
			return root->val > 0? root->val : 0;
		}
		int left = 0, right = 0;
		if(root->left){
			left = dfs(root->left, result);
		}
		if(root->right){
			right = dfs(root->right, result);
		}
		int cur = root->val + left + right;
		if(result < cur)
			result = cur;
		int add = left > right ? left : right;
		if(add < 0)	return root->val > 0? root->val : 0;
		return root->val + add > 0 ? root->val + add : 0;
	}

	int maxPathSum(TreeNode *root) {
		int result = INT_MIN;
		dfs(root, result);
		return result;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	TreeNode* root = (TreeNode*)malloc(DATASIZE*sizeof(TreeNode));
	int data[DATASIZE] = {-1,2,3,4,2,-6,-7};
	int count = 0;
	while(count < DATASIZE){
		root[count].val = data[count];
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

    int ret = sl.maxPathSum(root);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
