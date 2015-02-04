#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <deque>

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

	// recursively
	bool recursion(TreeNode* root, TreeNode* symm){
		if(!root && !symm)
			return true;
		if(!root || !symm)	return false;
		if(root->val != symm->val)	return false;
		if(root == symm)	return recursion(root->left, symm->right);
		return recursion(root->left, symm->right) && recursion(root->right, symm->left);
	}

	bool iteration(TreeNode* root){
		vector<TreeNode*> stl, str;
		vector<TreeNode*> tmpl, tmpr;
		
		stl.push_back(root->left);
		str.push_back(root->right);
		bool no_null = true;
		int sizel, sizer;
		while(no_null){
			no_null = false;
			sizel = stl.size();
			sizer = str.size();
			tmpl = stl;
			tmpr = str;
			stl.clear();
			str.clear();
			if(sizel != sizer) return false;
			for(int i = 0; i < sizer; i++){
				if(tmpl[i] && tmpr[i] && tmpl[i]->val == tmpr[i]->val){
					stl.push_back(tmpl[i]->left);
					stl.push_back(tmpl[i]->right);
					str.push_back(tmpr[i]->right);
					str.push_back(tmpr[i]->left);
					no_null = true;
					continue;
				}
				if(!tmpl[i] && !tmpr[i]){
					continue;
				}
				return false;
			}
		}
		return true;
	}

	bool isSymmetric_1st(TreeNode* root){
		if(root == NULL)
			return true;
		//return recursion(root, root);
		return iteration(root);
    }


	bool isSymmetric(TreeNode* root){
		if(!root) return true;
		deque<TreeNode*> left(1, root->left), right(1, root->right);
		TreeNode *l, *r;
		while(!left.empty() && !right.empty()){
			l = left.front();
			r = right.front();
			left.pop_front();
			right.pop_front();
			if(!l && !r)	continue;
			if(!l || !r || l->val != r->val)	return false;
			left.push_back(l->left);
			left.push_back(l->right);
			right.push_back(r->right);
			right.push_back(r->left);
		}
		return true;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	
	TreeNode* root = (TreeNode*)malloc(DATASIZE*sizeof(TreeNode));
	int data[] = {0,1,1,2,2,2,2};
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
	
	bool ret = sl.isSymmetric(root);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
