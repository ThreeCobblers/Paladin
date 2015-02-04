#include <iostream>
#include <string>
#include <stdlib.h>

#define DATASIZE 9

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
		if(root->left == NULL && root->right == NULL)
			return;

		TreeLinkNode* maxfather = root, *father;
		TreeLinkNode* maxson = root->left, *son;
		if(!maxson) maxson = root->right;
		while(maxson != NULL){
			son = maxson;
			father = maxfather;
			if(father->left != NULL && father->right){
				son->next = father->right;
				son = son->next;
			}
			while(father->next != NULL){
					father = father->next;
					if(father->left){
						son->next = father->left;
						son = son->next;
					}
					if(father->right){
						son->next = father->right;
						son = son->next;
					}
			}
			son->next = NULL;
			
			maxfather = maxson;
			while(maxfather->left == NULL && maxfather->right == NULL && maxfather->next != NULL)
				maxfather = maxfather->next;
			
			if(maxfather->left)
				maxson = maxfather->left;
			else
				maxson = maxfather->right;
		}	
    }

	void connect(TreeLinkNode *root) {
		if(!root)	return;
		TreeLinkNode *cur = root, *next, *last;
		cur->next = NULL;
		do{
			next = NULL;
			while(cur){
				if(cur->left){
					if(next){
						last->next = cur->left;
						last = last->next;
					}
					else{
						last = cur->left;
						next = last;
					}
				}
				if(cur->right){
					if(next){
						last->next = cur->right;
						last = last->next;
					}
					else{
						last = cur->left;
						next = last;
					}
				}
				cur = cur->next;
			}
			last->next = NULL;
			cur = next;
		}while(cur);
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

	root[4].right = &root[6];
	root[2].right = NULL;
	
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
