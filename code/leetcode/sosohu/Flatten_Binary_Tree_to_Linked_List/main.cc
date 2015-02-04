#include <iostream>
#include <string>
#include <stack>
#include <stdlib.h>

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

	void flatten_1st(TreeNode *root) {
		if(root == NULL)
			return;
		TreeNode* pos = root, * last = root;
		stack<TreeNode*> s;
		if(root->right)
			s.push(pos->right);
		if(root->left)
			s.push(pos->left);
		while(!s.empty()){
			pos = s.top();
			s.pop();
			last->right = pos;
			last->left = NULL;
			if(pos->right)
				s.push(pos->right);
			if(pos->left)
				s.push(pos->left);
			last = pos;
		}	
		last->left = NULL;
		last->right = NULL;
    }

	void flatten_2nd(TreeNode *root) {
		if(!root)	return;
		stack<TreeNode*> s;
		s.push(root);
		TreeNode *last = NULL, *cur;
		while(!s.empty()){
			cur = s.top();
			s.pop();
			if(last)
				last->right = cur;
			if(cur->right)
				s.push(cur->right);
			if(cur->left)
				s.push(cur->left);
			cur->left = NULL;
			last = cur;
		}
		last->right = NULL;
	}

	void flatten(TreeNode *root) {
		TreeNode *tail;
		recursion(root, tail);
	}

	TreeNode* recursion(TreeNode *root, TreeNode* &tail){
		if(!root)	return NULL;
		TreeNode *next = NULL;
		tail = root;
		if(root->left)
			next = recursion(root->left, tail);
		if(root->right)
			tail->right = recursion(root->right, tail);
		root->left = NULL;
		if(next)
			root->right = next;
		return root;
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

	sl.flatten(root);

	for(int i =0; i < DATASIZE; i++){
		if(root[i].right)
			cout<<root[i].val<<" "<<(root[i].right)->val<<endl;
		else
			cout<<root[i].val<<" NULL"<<endl;
	}
	

	return 0;

}
