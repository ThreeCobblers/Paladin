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

	bool hasCycle_1st(ListNode *head) {
		if(head == NULL || head->next == NULL) return false;
		ListNode* slow = head->next;
		ListNode* fast = head->next->next;	
		while(fast != NULL && slow != NULL){
			if(fast == slow){
				return true;
			}
			if(fast->next == NULL)
				return false;
			fast = fast->next->next;
			slow = slow->next;
		}
		return false;
	}

	ListNode *detectCycle(ListNode *head) {    
		if(head == NULL || head->next ==NULL) return head;
		ListNode* slow = head->next;
		ListNode* fast = head->next->next;	
		while(fast != NULL && slow != NULL){
			if(fast == slow){
				slow = head;
				while(slow != fast){
					slow = slow->next;
					fast = fast->next;	
				}
				return slow;
			}
			if(fast->next == NULL)
				return NULL;
			fast = fast->next->next;
			slow = slow->next;
		}
		return NULL;
	}

	bool hasCycle(ListNode *head) {
		if(!head)	return false;
		ListNode *slow = head, *fast = head;
		while(fast && fast->next){
			slow = slow->next;
			fast = fast->next->next;
			if(slow == fast)	return true;
		}
		return false;
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
	pos->next = &data[8]; 
//	pos->next = NULL; 
	pos->val = val[DATASIZE - 1]; 
	#ifdef DEBUG
	//print(head);	
	#endif
    pos = sl.detectCycle(head);
	if(pos == NULL)
		cout<<"NULL"<<endl;
	else
		cout<<pos->val<<endl;
	cout<<sl.hasCycle(head)<<endl;
	#ifdef DEBUG
	//print(head);	
	#endif
	free(data);
	return 0;

}
