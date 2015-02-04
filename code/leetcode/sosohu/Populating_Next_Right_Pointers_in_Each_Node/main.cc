#include <iostream>
#include <string>
#include <stdlib.h>

#define DATASIZE 7

using namespace std;

struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {

public:

	void connect_1st(TreeLinkNode *root) {
		if(root == NULL)
			return;

		root->next = NULL;
		if(root->left == NULL)
			return;

		TreeLinkNode* maxfather = root, *father;
		TreeLinkNode* maxson = root->left, *son;
		while(maxson != NULL){
			son = maxson;
			father = maxfather;
			son->next = father->right;
			son = son->next;
			while(father->next != NULL){
					father = father->next;
					son->next = father->left;
					son = son->next;
					son->next = father->right;
					son = son->next;
			}
			son->next = NULL;
			maxfather = maxson;
			maxson = maxfather->left;
		}	
    }

	void connect(TreeLinkNode *root) {
		if(!root)	return;
		TreeLinkNode *cur = root, *next;
		cur->next = NULL;
		while(cur->left){
			next = cur->left;
			while(cur){
				cur->left->next = cur->right;
				cur->right->next = cur->next? cur->next->left : NULL;
				cur = cur->next;
			}
			cur = next;
		}
	}
};

int main(int argc, char** argv)
{
	Solution sl;

	TreeLinkNode* root = (TreeLinkNode*)malloc(DATASIZE*sizeof(TreeLinkNode));
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
	
	sl.connect(root);

	for(int i = 0; i < DATASIZE; i++){
		TreeLinkNode* ret = root[i].next;
		cout<<i<<" ";
		if(ret == NULL)
			cout<<"NULL"<<endl;
		else
			cout<<ret->val<<endl;
	}

	return 0;

}
