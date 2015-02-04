#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <map>

#define DATASIZE 10

using namespace std;

struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {

public:

	RandomListNode *copyRandomList_1st(RandomListNode *head){
		if(head == NULL) return NULL;
		stack<RandomListNode*> to_be;
		unordered_map<RandomListNode*, RandomListNode*> have_new;
		RandomListNode* pos, *next, *rand;
		to_be.push(head);
		pos = head;
		RandomListNode* new_head, *new_pos, *new_next, *new_rand;
		new_head = new RandomListNode(head->label);
		new_pos = new_head;
		have_new[pos] = new_pos;
		while(!to_be.empty()){
			pos = to_be.top();
			to_be.pop();
			next = pos->next;
			rand = pos->random;
			new_pos = have_new[pos];
			if(next != NULL){
				if(have_new.count(next) == 1){
					new_pos->next = have_new[next];
				}
				else{
				 	new_next  = new RandomListNode(next->label);
					new_pos->next = new_next;
					have_new[next] = new_next;
					to_be.push(next);
				}
			}else{
				new_pos->next = NULL;
			}
			if(rand != NULL){
				if(have_new.count(rand) == 1){
					new_pos->random = have_new[rand];
				}
				else{
					new_rand = new RandomListNode(rand->label);
					new_pos->random = new_rand;
					have_new[rand] = new_rand;
					to_be.push(rand);
				}
			}else{
				new_pos->random = NULL;
			}
		}
		return new_head;
    }

	RandomListNode *copyRandomList(RandomListNode *head){
		if(!head)	return NULL;
		RandomListNode *pos = head, *tmp, *ret;
		while(pos){
			tmp = new RandomListNode(pos->label);	
			tmp->next = pos->next;
			pos->next = tmp;
			pos = pos->next->next;
		}
		pos = head;
		while(pos){
			pos->next->random = pos->random? pos->random->next : NULL;
			pos = pos->next->next;
		}
		pos = head;
		ret = pos->next;
		while(pos){
			tmp = pos->next;
			pos->next = tmp->next;
			tmp->next = pos->next? pos->next->next : NULL;
			pos = pos->next;
		}
		return ret;
	}

};

void clean(RandomListNode* data)
{
	if(data == NULL) return;
	stack<RandomListNode*> s;
	s.push(data);
	RandomListNode* pos;
	map<RandomListNode*,int> go;
	while(!s.empty()){
		pos = s.top();
		if(pos->next != NULL && go.count(pos->next) == 0)
			s.push(pos->next);
		if(pos->random != NULL && go.count(pos->random) == 0)
			s.push(pos->random);
		go[pos] = 1;
		s.pop();
	}
	map<RandomListNode*, int>::iterator iter;
	for(iter = go.begin(); iter != go.end(); iter++){
		cout<<"label "<<iter->first->label<<" ";
		cout<<"address "<<iter->first<<" ";
		cout<<"next "<<iter->first->next<<" ";
		cout<<"rand "<<iter->first->random<<endl;
		delete iter->first;
	}
}

int main(int argc, char** argv)
{
	Solution sl;
	vector<RandomListNode> r(DATASIZE,RandomListNode(0));
	for(int i = 0; i < DATASIZE; i++){
		r[i].label = i;
		r[i].next = &r[(i + 1) % DATASIZE];
		r[i].random = &r[(i + 1)%3];
	}
	r[DATASIZE - 1].next = NULL;
	cout<<"Data  :"<<endl;
	for(int i = 0; i < DATASIZE; i++){
		cout<<"label "<<r[i].label<<" ";
		cout<<"address "<<&r[i]<<" ";
		cout<<"next "<<r[i].next<<" ";
		cout<<"rand "<<r[i].random<<endl;
	}
	cout<<endl;

    RandomListNode* ret = sl.copyRandomList(&r[0]);

	cout<<__LINE__<<endl;
	
	/*
	cout<<"Result  :"<<endl;
	for(int i = 0; i < DATASIZE; i++){
		cout<<"label "<<r[i].label<<" ";
		cout<<"address "<<&r[i]<<" ";
		cout<<"next "<<r[i].next<<" ";
		cout<<"rand "<<r[i].random<<endl;
	}
	*/

	clean(ret);

	return 0;

}
