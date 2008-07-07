/* This is a double-ended queue. Not templated for sorting purposes. */

#ifndef _EVENT_DEQUE_H
#define _EVENT_DEQUE_H

#include "all_includes.h"

class EventDeque {
	private:
		DQNode* firstNode;
		DQNode* lastNode;
		int size;
		stdext::hash_map<int,DQNode*> tickIndex;
		std::vector<int> keyframes;

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