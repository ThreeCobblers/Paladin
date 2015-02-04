#include <iostream>
#include <stdlib.h>

using namespace std;

#define DATASIZE 13

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
	
	ListNode *swapPairs_1st(ListNode *head) {
		ListNode *newhead = new ListNode(0);
		newhead->next = head;
		ListNode *p1, *p2, *last;
		last = newhead;
		p1 = newhead->next;
		while(p1){
			p2 = p1->next;
			if(!p2)	break;
			last->next = p2;
			p1->next = p2->next;
			p2->next = p1;
			last = p1;
			p1 = p1->next;
		}
		return newhead->next;
	}

	ListNode *swapPairs(ListNode *head) {
		if(!head || !head->next)	return head;
		ListNode newhead(0), *first = &newhead, *second = &newhead;
		newhead.next = head;
		while(first->next && first->next->next){
			second = first->next;
			first->next = second->next;
			second->next = first->next->next;
			first->next->next = second;
			first = second;
		}
		return newhead.next;
	}

};

int main(int argc, char** argv)
{
	Solution sl;
	ListNode* data = (ListNode*)malloc(sizeof(ListNode)*DATASIZE);
	//int val[DATASIZE] = {-6,-3,3,1,4,5,10,3};
	int val[DATASIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
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
    head = sl.swapPairs(head);
	#ifdef DEBUG
	print(head);	
	#endif
	free(data);
	return 0;

}
