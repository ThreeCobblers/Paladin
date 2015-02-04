#include <iostream>
#include <stdlib.h>


using namespace std;

#define DATASIZE 8

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x ) : val(x), next(NULL) {}
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
	
	ListNode *reverseBetween_1st(ListNode *head, int m, int n) {
		if(m == n)	return head;

		ListNode* newhead = new ListNode(0);
		newhead->next = head;

		ListNode *pos, *start, *tmp, *smp;
		pos = newhead;
		for(int i = 0; i < m - 1; i++){
			pos = pos->next;
		}// pos is pre-node of start

		start = pos->next;

		for(int i = 0; i < n - m; i++){
			smp = pos->next;
			tmp = start->next;
			start->next = tmp->next;
			pos->next = tmp;
			tmp->next = smp;	
		}
		return newhead->next;
	}

	ListNode *reverseBetween(ListNode *head, int m, int n) {
		if(!head || !head->next || m >= n)	return head;
		ListNode newhead(0);
		newhead.next = head;
		ListNode *pos = &newhead, *next, *tmp;
		for(int i = 0; i < m - 1; i++){
			pos = pos->next;
		}
		next = pos->next;
		for(int i = 0; i < n - m; i++){
			tmp = next->next;
			next->next = tmp->next;
			tmp->next = pos->next;
			pos->next = tmp;
		}
		return newhead.next;
	}
};


int main(int argc, char** argv)
{
	Solution sl;
	ListNode* data = (ListNode*)malloc(sizeof(ListNode)*DATASIZE);
	int val[DATASIZE] = {2,-3,3,1,4,5,10,3};
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
    ListNode* ret = sl.reverseBetween(head, 3 , 5);
	#ifdef DEBUG
	print(ret);	
	#endif
	free(data);
	return 0;

}
