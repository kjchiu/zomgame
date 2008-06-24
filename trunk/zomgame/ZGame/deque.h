/* This is a double-ended queue. Not templated for sorting purposes. */

#ifndef _DEQUE_H
#define _DEQUE_H

#include "dq_node.h"

class Deque {
	private:
		DQNode* firstNode;
		DQNode* lastNode;
		int size;

	public:
		Deque();
		Deque(DQNode* firstNode);
		init(DQNode* firstNode);
		void addNode(DQNode* newNode); //appends a node (auto-sort?)
		void addNodeAt(DQNode* newNode); //places a node at a specific location
		DQNode* getFirstNode();
		DQNode* getLastNode();
		int getSize();
		Deque* sort();
		

};

#endif