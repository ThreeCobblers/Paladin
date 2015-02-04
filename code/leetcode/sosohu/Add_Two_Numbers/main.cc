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

	ListNode *addTwoNumbers_1st(ListNode *l1, ListNode *l2) {
		if(!l1)	return l2;
		if(!l2)	return l1;
		ListNode *p1, *p2, *p;
		p1 = l1;
		p2 = l2;
		int cin = 0;
		p2->val = p1->val + p2->val + cin;
		cin = p2->val / 10;
		p2->val = p2->val % 10;
		while(p1->next && p2->next){
			p2->next->val = p1->next->val + p2->next->val + cin;
			cin = p2->next->val / 10;
			p2->next->val = p2->next->val % 10;
			p1 = p1->next;
			p2 = p2->next;
		}
		if(p1->next){
			p2->next = p1->next;
			while(cin && p1->next){
				p1->next->val = p1->next->val + cin;
				cin = p1->next->val / 10;
				p1->next->val = p1->next->val % 10;
				p1 = p1->next;
			}
			if(cin){
				p1->next = new ListNode(cin);
			}
			return l2;
		}	
		while(cin && p2->next){
			p2->next->val = p2->next->val + cin;
			cin = p2->next->val / 10;
			p2->next->val = p2->next->val % 10;
			p2 = p2->next;
		}
		if(cin){
			p2->next = new ListNode(cin);
		}
		return l2;
    }	
	
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		ListNode head(0), *ret = &head;
		int cin = 0, val;
		while(l1 || l2 || cin){
			val = (l1? l1->val : 0) + (l2? l2->val : 0) + cin;
			ret = ret->next = new ListNode(val % 10);
			cin = val / 10;
			if(l1)	l1 = l1->next;
			if(l2)	l2 = l2->next;
		}
		return head.next;
	}

};


int main(int argc, char** argv)
{
	Solution sl;
	ListNode* data = (ListNode*)malloc(sizeof(ListNode)*DATASIZE);
	int val[DATASIZE] = {9,9,9,9,9,9,9,9};
	ListNode* head, *pos, *l1, *l2; 
	pos = &data[0];
	head = pos;
	for(int i = 0; i < DATASIZE - 1  ; i++){
		pos->next = &data[i+1];
		pos->val = val[i];
		pos = pos->next;
	}		
	pos->next = NULL; 
	pos->val = val[DATASIZE - 1]; 
	l1 = head;
	data[2].next = NULL;
	l2 = &data[3];
	#ifdef DEBUG
	print(head);	
	#endif
    head = sl.addTwoNumbers(l1, l2);
	#ifdef DEBUG
	print(head);	
	#endif
	free(data);
	return 0;

}
