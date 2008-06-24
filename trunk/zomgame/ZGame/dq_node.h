/* This is a node in a double-ended queue. Not templated as to have sorting capabilities. */

#ifndef _DQNODE_H
#define _DQNODE_H

#include <stdio.h>

class DQNode {
	private:
		DQNode* nextNode;
		DQNode* prevNode;
		//put data here

	public:
		DQNode();
		DQNode(DQNode* nPrevNode);
		DQNode(DQNode* nPrevNode, DQNode* nNextNode);
		void init(DQNode* nPrevNode, DQNode* nNextNode);
		//add a constructor taking data, too
		DQNode* getNextNode();
		DQNode* getPrevNode();
		void setNextNode(DQNode* nNextNode);
		void setPrevNode(DQNode* nPrevNode);
		//getData()
};

#endif