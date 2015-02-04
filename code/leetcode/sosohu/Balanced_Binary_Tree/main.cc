#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

#define DATASIZE 10

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {

public:
	
	bool detail(TreeNode* root, int& deepth){
		int left = 0, right = 0;
		bool isleft = true, isright = true;
		if(root->left)
			isleft = detail(root->left, left);
		if(root->right)
			isright = detail(root->right, right);

		deepth = left > right ? left : right;
		deepth++;

		if(!isleft || !isright)
			return false;

		if(abs(left - right) > 1 )
			return false;

		return true;
	}

	bool isBalanced_1st(TreeNode *root) {
		if(root == NULL)
			return true;
		int deepth;
		return detail(root, deepth);
    }

	bool dfs(TreeNode *root, int &hight){
		if(!root){
			hight = 0;
			return true;
		}
		int left, right;
		bool is_left = dfs(root->left, left);
		bool is_right = dfs(root->right, right);
		hight = left > right? left + 1 : right + 1;
		return is_left && is_right && (abs(left - right) < 2);
	}

	bool isBalanced(TreeNode *root) {
		int hight;
		return dfs(root, hight);
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

	root[4].left = NULL;
	root[7].left = &root[9];
	
	bool ret = sl.isBalanced(root);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
