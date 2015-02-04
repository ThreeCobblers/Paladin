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
	
	ListNode *reverseKGroup_1st(ListNode *head, int k) {
		ListNode *newhead = new ListNode(0);
		newhead->next = head;
		ListNode *pos, *last_head, *last_tail, *tmp;
		int count = 0;
		pos = newhead;
		while(pos->next != NULL){
			last_head = pos;
			pos = pos->next;
			count = 0;
			for(; count < k - 1 && pos->next != NULL; count++){
				if(last_head != pos){
					tmp = pos->next;
					pos->next = tmp->next;
					tmp->next = last_head->next;
					last_head->next = tmp;
				}
			}
			if(pos->next == NULL && count != k -1){
				pos = last_head->next;
				for(int i = 0; i < count; i++){
					tmp = pos->next;
					pos->next = tmp->next;
					tmp->next = last_head->next;
					last_head->next = tmp;
				}
				break;
			}
		}
		return newhead->next;
	}

	ListNode *reverseKGroup(ListNode *head, int k) {
		if(!head || k <= 1)	return head;
		ListNode newhead(0), *first = &newhead, *second = &newhead, *pos = head;
		newhead.next = head;
		int count = 0;
		while(pos){
			pos = pos->next;
			count++;
		}
		while(count >= k){
			second = first->next;
			for(int i = 0; i < k - 1; i++){
				pos = second->next;
				second->next = pos->next;
				pos->next = first->next;
				first->next = pos;
			}
			count = count - k;
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
    head = sl.reverseKGroup(head,5);
	#ifdef DEBUG
	print(head);	
	#endif
	free(data);
	return 0;

}
