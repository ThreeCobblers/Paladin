#include <iostream>
#include <stdlib.h>

using namespace std;

#define DATASIZE 10

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

void print(ListNode* data)
{
	ListNode* pos = data;
	cout<<"Result  :"<<endl;
	while(pos != NULL)
	{
		cout<<"val: "<<pos->val<<endl;
		pos = pos->next;
	}
}

class Solution {

public:

	void reorderList_1st(ListNode *head) {
		if(head == NULL || head->next == NULL) return;
		ListNode* pos = head;
		int len = 0;
		while(pos != NULL){
			pos = pos->next;
			len++;
		}
		int mid = len / 2;
		pos = head;
		for(int i = 0; i < mid - 1; i++){
			pos = pos->next;
		}
		ListNode sub_header(0);
		sub_header.next = pos->next;
		// revers
		ListNode* sub_pos = pos->next;
		ListNode* tmp, *smp;
		while(sub_pos->next != NULL){
			tmp = sub_pos->next;
			sub_pos->next = tmp->next;
			tmp->next = sub_header.next;
			sub_header.next = tmp;
		}
		sub_pos = &sub_header;
		pos->next = NULL;
		pos = head;
		while(pos != NULL && sub_pos != NULL){
			tmp = sub_pos->next;
			smp = pos->next;
			sub_pos->next = pos;
			pos->next = tmp;
			pos = smp;
			sub_pos = sub_pos->next->next;
		}
		head = sub_header.next;
	}

	void reorderList(ListNode *head) {
		if(!head || !head->next)	return;
		ListNode *slow = head, *fast = head->next, *left = head, *right, *tmp;
		while(fast && fast->next){
			slow = slow->next;
			fast = fast->next->next;
		}
		right = slow->next;
		while(right->next){
			tmp = right->next;
			right->next = tmp->next;
			tmp->next = slow->next;
			slow->next = tmp;
		}
		right = slow->next;
		slow->next = NULL;
		while(left->next){
			tmp = right->next;
			right->next = left->next;
			left->next = right;
			right = tmp;
			left = left->next->next;
		}
		left->next = right;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	ListNode* data = (ListNode*)malloc(sizeof(ListNode)*DATASIZE);
	//int val[DATASIZE] = {-6,-3,3,1,4,5,10,3};
	int val[DATASIZE] = {1,2,3,4,5,6,7,8,9,10};
	ListNode* head, *pos; 
	pos = &data[0];
	head = pos;
	for(int i = 0; i < DATASIZE - 1  ; i++){
		pos->next = &data[i+1];
		pos->val = val[i];
		pos = pos->next;
	}		
	pos->next = NULL; 
	pos->val = val[DATASIZE - 1]; 
	#ifdef DEBUG
	print(head);	
	#endif
    sl.reorderList(head);
	#ifdef DEBUG
	print(head);	
	#endif
	free(data);
	return 0;

}
