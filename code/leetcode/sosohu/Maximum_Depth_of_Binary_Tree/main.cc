#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>
#include <climits>

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
	
	int maxDepth_1st(TreeNode *root) {
		if(root == NULL)
			return 0;
		if(root->left == NULL && root->right == NULL)
			return 1;

		int left = 0, right = 0;
		int deepth ;

		if(root->left)
			left = maxDepth(root->left);
		if(root->right)
			right = maxDepth(root->right);
		deepth = left;
		if(!root->left)
			deepth = right;
		else{
			 if(root->right)
				deepth = left > right? left : right;
		}
		deepth++;
		return deepth;		
    }

	int maxDepth(TreeNode *root) {
		if(!root)	return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);
		return left < right? right + 1 : left + 1;
	}

	//前序迭代
	int maxDepth_iter(TreeNode *root) {
		if(!root)	return 0;
		stack<pair<TreeNode*, int> > s;
		s.push(make_pair(root, 1));
		pair<TreeNode*, int> curr;
		int result = INT_MIN;
		while(!s.empty()){
			curr = s.top();
			s.pop();
			if(!curr.first->left && !curr.first->right){
				if(result < curr.second)
					result = curr.second;
				continue;
			}
			if(curr.first->left){
				s.push(make_pair(curr.first->left, curr.second + 1));
			}
			if(curr.first->right){
				s.push(make_pair(curr.first->right, curr.second + 1));
			}
		}
		return result;
	}

	// learned by boya
	int maxDepth_iter_2nd(TreeNode *root) {
		if(!root)	return 0;
		stack<TreeNode*>	s;
		s.push(root);
		TreeNode *curr = root, *last = NULL;
		while(!s.empty()){
			if(curr){
				if(curr->left == last || curr->right == last){
					last = curr;
					cur = s.top();
					s.pop();
				}else{
					s.push(curr->left);
				}
			}else{
				curr = s.top();
				if(curr->right)
					s.push(curr->right);
			}
		}
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
	
	int ret = sl.maxDepth(root);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
