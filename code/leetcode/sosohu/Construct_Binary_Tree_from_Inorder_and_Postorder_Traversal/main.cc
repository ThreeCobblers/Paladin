#include <iostream>
#include <vector>
#include <string>

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

	TreeNode* detail(vector<int> &inorder, vector<int> &postorder, int in_start, int in_end, int post_start, int post_end){
		if(in_start > in_end || post_start > post_end)
			return NULL;
		int val = postorder[post_end];
		TreeNode* father = new TreeNode(val);
		int in_pos = in_start, post_pos = post_start;
		for(; in_pos <= in_end; in_pos++, post_pos++){
			if(inorder[in_pos] == val)
				break;
		}
		TreeNode *left = NULL, *right = NULL;
		
		left = detail(inorder, postorder, in_start, in_pos - 1, post_start, post_pos - 1);
		right = detail(inorder, postorder, in_pos + 1, in_end, post_pos, post_end - 1);

		father->left = left;
		father->right = right;

		return father;
	}

	TreeNode *buildTree_1st(vector<int> &inorder, vector<int> &postorder) {
		int size = inorder.size();
		if(size == 0)
			return NULL;
		return detail(inorder, postorder, 0, size - 1, 0, size - 1);
    }

	TreeNode* recursion(vector<int> &inorder, vector<int> &postorder,
							int s_in, int e_in, int s_po, int e_po){
		if(s_in > e_in)	return NULL;
		if(s_in == e_in) return (new TreeNode(inorder[s_in]));
		TreeNode *root = new TreeNode(postorder[e_po]);
		int split_in, split_po;
		for(split_in = s_in; split_in <= e_in; split_in++){
			if(postorder[e_po] == inorder[split_in])
				break;
		}
		split_po = s_po + split_in - s_in;
		root->left = recursion(inorder, postorder, s_in, split_in - 1, s_po , split_po - 1 );
		root->right = recursion(inorder, postorder, split_in + 1, e_in, split_po, e_po - 1);
		return root;
	}

	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
		if(inorder.size() != postorder.size() || inorder.size() == 0)
			return NULL;
		return recursion(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	vector<int> inorder, postorder;
	for(int i = 0; i < 5; i++)
		inorder.push_back(i);
	postorder.push_back(1);
	postorder.push_back(0);
	postorder.push_back(3);
	postorder.push_back(4);
	postorder.push_back(2);

    TreeNode* ret = sl.buildTree(inorder, postorder);
	
	prePrint(ret);

	return 0;

}
