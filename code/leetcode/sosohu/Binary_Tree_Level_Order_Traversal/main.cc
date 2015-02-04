#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#define DATASIZE 10

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
	cout<<root->val<<endl;	
	if(root->left){
		prePrint(root->left);
	}
	if(root->right){
		prePrint(root->right);
	}
}

class Solution {

public:

	vector<vector<int> > levelOrder_1st(TreeNode *root) {
		vector<vector<int> > data;
		vector<vector<TreeNode*> > tree;
		if(root == NULL)
			return data;
		vector<TreeNode*> vec;
		vec.push_back(root);
		tree.push_back(vec);

		bool hasnext = true;
		int i = 0;
		TreeNode* tmp;
		while(hasnext){
			vec.clear();
			for(int j = 0; j < tree[i].size(); j++){
				tmp = tree[i][j];
				if(tmp->left)
					vec.push_back(tmp->left);
				if(tmp->right)
					vec.push_back(tmp->right);
			}
			if(vec.size() != 0)
				tree.push_back(vec);
			else
				hasnext = false;
			i++;
		}
		for(int j = 0; j < tree.size(); j++){
			vector<int> v;
			for(int k = 0; k < tree[j].size(); k++)
				v.push_back(tree[j][k]->val);
			data.push_back(v);
		}
		return data;
	}

	vector<vector<int> > levelOrder(TreeNode *root) {
		vector<vector<int> > data;
		if(!root)	return data;
		vector<TreeNode*> cur, next;
		next.push_back(root);
		int count = 0;

		while(1){
			vector<int> tmp;
			cur = next;
			next.clear();
			for(int i = 0; i < cur.size(); i++){
				tmp.push_back(cur[i]->val);
				if(cur[i]->left)
					next.push_back(cur[i]->left);
				if(cur[i]->right)
					next.push_back(cur[i]->right);
			}
			data.push_back(tmp);
			if(next.empty())	break;
		}
		return data;
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

	vector<vector<int> > ret = sl.levelOrder(root);

	for(int i = 0; i < ret.size(); i++){
		for(int j = 0; j < ret[i].size(); j++)
			cout<<ret[i][j]<<" ";
		cout<<endl;
	}

	return 0;

}
