#include "deque.h"

Deque::Deque(){
	firstNode = NULL;
	size = 0;
}

Deque::Deque(DQNode *nFirstNode){
	firstNode = nFirstNode;
	tickIndex.insert(std::pair<int, DQNode*>(nFirstNode->getEventTick(), nFirstNode));
	size = 1;
}

void Deque::addNode(DQNode *newNode){
	if (getFirstNode() == NULL || getFirstNode()->getEventTick() > newNode->getEventTick()){
		newNode->setNextNode(firstNode);
		firstNode = lastNode = newNode;
		tickIndex.insert(std::pair<int, DQNode*>(newNode->getEventTick(), newNode));
		size++;
		return;
	}
	DQNode* checkNode = getNodeAtTick(newNode->getEventTick());
	 //where to begin the search for sorting purposes
	if (checkNode == NULL){
		tickIndex.insert(std::pair<int, DQNode*>(newNode->getEventTick(), newNode));
		checkNode = getFirstNode();
	}
	while (checkNode->getNextNode() != NULL && checkNode->getNextNode()->getEventTick() <= newNode->getEventTick()){
		checkNode = checkNode->getNextNode();
	}
	
	newNode->setPrevNode(checkNode);
	if (checkNode->getNextNode() != NULL){
		newNode->setNextNode(checkNode->getNextNode());
		checkNode->getNextNode()->setPrevNode(newNode);
	} else {
		lastNode = newNode;
	}
	checkNode->setNextNode(newNode);
	size++;
}

DQNode* Deque::getFirstNode(){
	return firstNode;
}

DQNode* Deque::getLastNode(){
	return lastNode;
}

DQNode* Deque::getNodeAtTick(int tick){
	if (tickIndex.find(tick) == tickIndex.end()){
		return NULL;
	} 
	return tickIndex.find(tick)->second;	
}