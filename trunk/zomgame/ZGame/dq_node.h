/* This is a node in a double-ended queue. Not templated as to have sorting capabilities. */

#ifndef _DQNODE_H
#define _DQNODE_H

#include <stdio.h>
#include "event.h"


class DQNode {
	private:
		DQNode* nextNode;
		DQNode* prevNode;
		Event* eventData;

	public:
		DQNode();
		DQNode(DQNode* nPrevNode);
		DQNode(DQNode* nPrevNode, DQNode* nNextNode);
		~DQNode();
		void init(DQNode* nPrevNode, DQNode* nNextNode);
		Event* getEventData();
		int getEventTick();
		DQNode* getNextNode();
		DQNode* getPrevNode();
		void setEventData(Event* nEventData);
		void setNextNode(DQNode* nNextNode);
		void setPrevNode(DQNode* nPrevNode);
		
};

#endif