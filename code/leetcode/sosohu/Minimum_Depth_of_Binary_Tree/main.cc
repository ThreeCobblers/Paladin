#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <stack>
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
	
	 int minDepth_1st(TreeNode *root) {
		if(root == NULL)
			return 0;
		if(root->left == NULL && root->right == NULL)
			return 1;

		int left = 0, right = 0;
		int deepth ;

		if(root->left)
			left = minDepth(root->left);
		if(root->right)
			right = minDepth(root->right);
		deepth = left;
		if(!root->left)
			deepth = right;
		else{
			 if(root->right)
				deepth = left < right? left : right;
		}
		deepth++;
		return deepth;		
    }

	int minDepth_2nd(TreeNode *root) {
		if(!root)	return 0;
		if(!root->left && !root->right)	return 1;
		if(!root->left)
			return minDepth(root->right) + 1;
		if(!root->right)
			return minDepth(root->left) + 1;
		return min(minDepth(root->left), minDepth(root->right)) + 1;
	}

	
	void dfs(TreeNode *root, int &result, int depth){
		if(result < depth + 1) return;
		if(!root->left && !root->right){
			result = depth + 1;
			return;
		}
		if(root->left)
			dfs(root->left, result, depth + 1);
		if(root->right)
			dfs(root->right, result, depth + 1);
	}

	int minDepth_3nd(TreeNode *root) {
		if(!root)	return 0;
		int result = INT_MAX;
		dfs(root, result, 0);
		return result;
	}

	// iteraterion version
	int minDepth(TreeNode *root) {
		if(!root)	return 0;
		stack<pair<TreeNode*, int> > s;
		s.push(make_pair(root, 1));
		int	 result = -((1<<31) + 1);
		TreeNode *node;
		int depth;
		while(!s.empty()){
			node = s.top().first;
			depth = s.top().second;
			s.pop();
			if(result < depth)	continue;
			if(!node->left && !node->right)
				result = depth;

			if(node->left )
				s.push(make_pair(node->left, depth + 1));
			if(node->right)
				s.push(make_pair(node->right, depth + 1));
		}
		return result;
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
	
	int ret = sl.minDepth(root);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
