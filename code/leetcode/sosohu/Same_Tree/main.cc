#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

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

	bool isSameTree_1st(TreeNode *p, TreeNode *q) {
		if(p == NULL && q == NULL)
			return true;
		if(p == NULL)	return false;
		if(q == NULL)	return false;
		if(p->val != q->val)	return false;

		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }


	bool isSameTree(TreeNode *p, TreeNode *q) {
		if(!p && !q)	return true;
		if(!p || !q || p->val != q->val)	return false;
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	
	TreeNode* root = (TreeNode*)malloc(DATASIZE*sizeof(TreeNode));
	int data[] = {0,1,1,2,1,2,2};
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
	
	bool ret = sl.isSameTree(root, &root[2]);
	
	cout<<"Result  :("<<ret<<")"<<endl;

	return 0;

}
