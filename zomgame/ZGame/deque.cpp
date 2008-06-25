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

//hmm
void Deque::removeNode(DQNode *remNode){
	//manage the hash map
	if (getNodeAtTick(remNode->getEventTick()) == remNode){ //if remNode is the one in the hash, remove it
		tickIndex.erase(remNode->getEventTick());
		if (remNode->getNextNode()->getEventTick() == remNode->getEventTick()){ 
			//and if the next node also equals remNode, add that node to the hash
			tickIndex.insert(std::pair<int, DQNode*>(remNode->getEventTick(), remNode->getNextNode()));
		}
	}
	//take care of the deque
	if (remNode == getFirstNode()){
		firstNode = remNode->getNextNode();
	}
	if (remNode == getLastNode()){
		lastNode = remNode->getPrevNode();
	}
	if (size > 1){
		if (remNode != getLastNode()) {remNode->getNextNode()->setPrevNode(remNode->getPrevNode());}
		if (remNode != getFirstNode()){remNode->getPrevNode()->setNextNode(remNode->getNextNode());}
	}
	size--;
}