/* This is a double-ended queue. Not templated for sorting purposes. */

#ifndef _DEQUE_H
#define _DEQUE_H

#include "dq_node.h"
#include <hash_map>

class Deque {
	private:
		DQNode* firstNode;
		DQNode* lastNode;
		int size;
		stdext::hash_map<int,DQNode*> tickIndex;

	public:
		Deque();
		Deque(DQNode* nfirstNode);
		void addNode(DQNode* newNode); //appends a node (auto-sort?)
		void addNodeAt(DQNode* newNode, int index); //places a node at a specific location
		DQNode* getFirstNode();
		DQNode* getLastNode();
		DQNode* getNodeAtTick(int tick);
		int getSize();
		void removeNode(DQNode* remNode);	
};

#endif