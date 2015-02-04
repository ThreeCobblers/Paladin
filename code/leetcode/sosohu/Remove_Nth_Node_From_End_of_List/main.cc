#include <iostream>
#include <string>
#include <cstdlib>

#define DATASIZE 8

using namespace std;


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

	ListNode *removeNthFromEnd_1st(ListNode *head, int n) {
		ListNode *newhead = new ListNode(0), *pos = newhead, *last = newhead;
		newhead->next = head;
		if(n == 0)	return head;
		for(int i = 0; i < n; i++)
			last = last->next;
		while(last->next != NULL){
			pos = pos->next;
			last = last->next;
		}
		pos->next = pos->next->next;
		return newhead->next;
    }

	
	ListNode *removeNthFromEnd(ListNode *head, int n) {
		if(!head || n < 1)	return head;
		ListNode newhead(0);
		newhead.next = head;
		ListNode *last = &newhead, *first = &newhead;
		while(n-- > 0 && last->next){
			last = last->next;
		}
		while(last->next){
			first = first->next;
			last = last->next;
		}
		first->next = first->next->next;
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
    head = sl.removeNthFromEnd(head, 3);
	#ifdef DEBUG
	print(head);	
	#endif
	free(data);

	return 0;

}
