/* This is a double-ended queue. Not templated for sorting purposes. */

#ifndef _DEQUE_H
#define _DEQUE_H

#include "dq_node.h"
#include <hash_map>

class EventDeque {
	private:
		DQNode* firstNode;
		DQNode* lastNode;
		int size;
		stdext::hash_map<int,DQNode*> tickIndex;

	public:
		EventDeque();
		EventDeque(DQNode* nfirstNode);
		void addNode(DQNode* newNode); //appends a node (auto-sort)
		void addNode(Event* ev);
		DQNode* getFirstNode();
		DQNode* getLastNode();
		DQNode* getFirstNodeAtTick(int tick);
		DQNode* getLastNodeAtTick(int tick);
		EventDeque* getNodesBetween(int start, int end);
		int getSize();
		void removeNode(DQNode* remNode);	
};

#endif