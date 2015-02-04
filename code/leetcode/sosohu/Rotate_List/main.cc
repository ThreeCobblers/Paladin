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

	ListNode *rotateRight_1st(ListNode *head, int k) {
		if(head == NULL)	return NULL;
		if(k == 0)	return head;
		int len = 0;
		ListNode *pos1, *pos2;
		pos2 = head;
		while(pos2 != NULL && len < k){
			pos2 = pos2->next;
			len++;
		}
		if(!pos2) return rotateRight(head, k%len);
		pos1 = head;
		pos2 = head; 
		for(int i = 0; i < k; i++){
			pos2 = pos2->next;
		}
		while(pos2->next != NULL){
			pos1 = pos1->next;
			pos2 = pos2->next;
		}
		ListNode* last = pos1;
		pos1 = pos1->next;
		pos2->next = head;	
		last->next = NULL;
		return pos1;
    }	

	ListNode *rotateRight(ListNode *head, int k) {
		if(!head || k < 1)	return head;
		ListNode *pos = head, *pre = head;
		int count = 0;
		for(; count < k && pos; count++){
			pos = pos->next;
		}
		if(!pos)	return rotateRight(head, k%count);
		while(pos->next){
			pos = pos->next;
			pre = pre->next;
		}
		pos->next = head;
		head = pre->next;
		pre->next = NULL;
		return head;
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
    head = sl.rotateRight(head, 3);
	#ifdef DEBUG
	print(head);	
	#endif
	free(data);
	return 0;

}
