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

	vector<vector<int> > zigzagLevelOrder_1st(TreeNode *root) {
		vector<vector<int> > data;
		vector<vector<TreeNode*> > tree;
		
		if(root == NULL)
			return data;

		bool hasnext = true;
		vector<TreeNode*> vec_t;
		vector<int> vec;
		vec_t.push_back(root);
		tree.push_back(vec_t);
		TreeNode* tmp;
		int i = 0;
		while(hasnext){
			vec_t.clear();
			for(int j = 0; j < tree[i].size(); j++){
				tmp = tree[i][j];
				if(tmp->left)
					vec_t.push_back(tmp->left);
				if(tmp->right)
					vec_t.push_back(tmp->right);
			}
			if(vec_t.size() == 0)
				hasnext = false;
			else
				tree.push_back(vec_t);
			i++;
		}

		for(int j = 0; j < tree.size(); j++){
			vec.clear();
			if(j%2 == 0){
				for(int k = 0; k < tree[j].size(); k++){
					vec.push_back((tree[j][k])->val);
				}
			}else{
				for(int k = tree[j].size()-1; k >= 0; k--){
					vec.push_back((tree[j][k])->val);
				}
			}
			data.push_back(vec);
		}
		return data;
	}

	vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
		vector<vector<int> > data;
		if(!root)	return data;
		vector<TreeNode*> cur, next;
		next.push_back(root);
		bool left_right = true;
		while(1){
			vector<int> tmp;
			cur = next;
			next.clear();
			int size = cur.size();
			for(int i = 0; i < size; i++){
				if(cur[i]->left)
					next.push_back(cur[i]->left);
				if(cur[i]->right)
					next.push_back(cur[i]->right);
				if(left_right)
					tmp.push_back(cur[i]->val);
				else
					tmp.push_back(cur[size - 1 - i]->val);
			}
			data.push_back(tmp);
			left_right = !left_right;
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

	vector<vector<int> > ret = sl.zigzagLevelOrder(root);

	for(int i = 0; i < ret.size(); i++){
		for(int j = 0; j < ret[i].size(); j++)
			cout<<ret[i][j]<<" ";
		cout<<endl;
	}

	return 0;

}
