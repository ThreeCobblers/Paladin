#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cassert>

#define DATASIZE 6

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void prePrint(TreeNode* root){
	if(root == NULL)
		return;
	if(root->left){
		prePrint(root->left);
	}
	cout<<root->val<<endl;	
	if(root->right){
		prePrint(root->right);
	}
}


class Solution {

public:
	void inorder(TreeNode* root,  TreeNode*& first_node, TreeNode*& second_node, int& count, TreeNode*& ret){
		if(root == NULL)	return;
		int val = root->val;

		if(root->left)
			inorder(root->left, first_node, second_node, count, ret);

		int l_val;

		if(ret && val < ret->val){
			if(!first_node){
				first_node = ret;
			}
			second_node = root;
		}

		count++;
		ret = root;

		if(root->right)
			inorder(root->right,  first_node, second_node, count, ret);
	}

	inline void swap(int& lv, int& rv){
		lv = lv - rv;
		rv = lv + rv;
		lv = rv - lv;
	}

	void recoverTree_1st(TreeNode* root) {
		TreeNode *first_node = NULL, *second_node = NULL, *ret = NULL;
		int count = 0;
		inorder(root, first_node, second_node, count, ret);
		
		#ifdef DEBUG
		cout<<"first: "<<first_node->val<<" second: "<<second_node->val<<endl;
		#endif
		swap(first_node->val, second_node->val);
    }

	void dfs(TreeNode* root, int& last, TreeNode* &first, TreeNode* &second){
		if(root->left){
			dfs(root->left, last, first, second);
		}
		if(root->val < last){
			second = root;
		}
		if(!second){
			first = root;
		}
		last = root->val;
		if(root->right){
			dfs(root->right, last, first, second);
		}
	}

	void recoverTree(TreeNode* root) {
		if(!root)	return;
		TreeNode *first = NULL, *second = NULL;
		int min = (-1)<<31;
		dfs(root, min, first, second);
		int tmp = first->val;
		first->val = second->val;
		second->val = tmp;
	}

	//迭代
	void recoverTree_iter(TreeNode* root) {
		if(!root)	return;
		TreeNode *first = NULL, *second = NULL, *cur;
		int last = INT_MIN;
		stack<TreeNode*> s;
		s.push(root);
		while(!s.empty()){
			cur = s.top();
			while(cur){
				s.push(cur->left);
				cur = cur->left;
			}
			s.pop();
			if(!s.empty()){
		    	cur = s.top();
		    	if(cur->val < last){
		    		second = cur;
		    	}
		    	if(!second){
				    first = cur;
			    }
			    last = cur->val;
			    s.pop();
			    s.push(cur->right);
			}
		}
		int tmp = first->val;
		first->val = second->val;
		second->val = tmp;
	}
};

int main(int argc, char** argv)
{
	Solution sl;
	
	TreeNode* root = (TreeNode*)malloc(DATASIZE*sizeof(TreeNode));
	//int data[] = {2,3,1};
	int data[] = {4,1,5,0,2,3};
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

	prePrint(root);
	
	sl.recoverTree(root);
	
	prePrint(root);
	

	return 0;

}
