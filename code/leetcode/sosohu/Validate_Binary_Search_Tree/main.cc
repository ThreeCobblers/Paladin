#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
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

	bool MIN;

public:
	bool recursion(TreeNode* root, TreeNode*& last){
		bool left = true, right = true;
		if(root->left)
			left = recursion(root->left, last);	
		if(!left) return false;

		if(last && last->val >= root->val)
				return false;
		last = root;

		if(root->right)
			right = recursion(root->right, last);
		if(!right)	return false;

		return true;
	}

	bool isValidBST_1st(TreeNode *root) {
		if(root == NULL)
			return true;

		TreeNode* last = NULL;
		return recursion(root, last);
	}

	bool dfs(TreeNode *root, int& up){
		if(!root)	return true;
		if(root->left){
			bool left =  dfs(root->left, up);
			if(!left) return false;
		}
		if(root->val <= up && (MIN || up != (-1)<<31)){
		    return false;
		}	
	    if(root->val == (-1)<<31)
			MIN = true;
		up = root->val;
		if(root->right){
			bool right = dfs(root->right, up);
			if(!right)	return false;
		}
		return true;
	}

	bool isValidBST(TreeNode *root) {
		if(!root)	return true;
		int up = (-1)<<31;
		MIN = false;
		return dfs(root, up);
	}

	//迭代
	bool isValidBST_Stack(TreeNode *root) {
		if(!root)	return false;
		stack<TreeNode*> s;
		TreeNode *p = root;
		s.push(root);
		while(p->left){
			s.push(p->left);
			p = p->left;
		}
		int last = p->val;
		s.pop();
		if(p->right){
			s.push(p->right);
			p = p->right;
			while(p->left){
				s.push(p->left);
				p = p->left;
			}
		}
		while(!s.empty()){
			p = s.top();
			s.pop();
			if(last >= p->val) return false;
			last = p->val;
			if(p->right){
				s.push(p->right);
				p = p->right;
				while(p->left){
					s.push(p->left);
					p = p->left;
				}
			}
		}
		return true;
	}

	bool isValidBST_Mirror(TreeNode *root) {
		if(!root)	return true;
		TreeNode *curr = root, *next;
		int last = INT_MIN;
		bool isFirst = true;
		bool ret = true;
		while(curr){
			if(!curr->left){
				if(!isFirst && curr->val <= last){
					ret = false;
				}
				if(isFirst)
					isFirst = false;
				last = curr->val;
				curr = curr->right;
				continue;
			}
			next = curr->left;
			while(next->right){
				if(next->right == curr)	break;
				next = next->right;
			}
			if(next->right == curr){
				next->right = NULL;
				if(!isFirst && curr->val <= last){
					ret = false;
				}
				if(isFirst)
					isFirst = false;
				last = curr->val;
				curr = curr->right;
			}else{
				next->right = curr;
				curr = curr->left;
			}
		}
		return ret;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	
	TreeNode* root = (TreeNode*)malloc(DATASIZE*sizeof(TreeNode));
	int data[] = {1,1,5,0,2,4,6};
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
	root[0].val = 10;	
	root[1].val = 5;	
	root[2].val = 15;	
	root[3].val = 6;	
	root[4].val = 20;	
	root[0].right = &root[2];
	root[0].left = &root[1];
	root[1].left = NULL;
	root[1].right = NULL;
	root[2].left = &root[3];
	root[2].right = &root[4];
	root[3].left = NULL;
	root[3].right = NULL;
	root[4].left = NULL;
	root[4].right = NULL;
	bool ret = sl.isValidBST_Mirror(root);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
