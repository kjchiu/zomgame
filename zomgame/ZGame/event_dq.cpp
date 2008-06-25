#include "event_dq.h"

EventDeque::EventDeque(){
	firstNode = lastNode = NULL;
	size = 0;
}

EventDeque::EventDeque(DQNode *nFirstNode){
	firstNode = lastNode = nFirstNode;
	tickIndex.insert(std::pair<int, DQNode*>(nFirstNode->getEventTick(), nFirstNode));
	size = 1;
}

void EventDeque::addNode(Event* ev){
	DQNode* dqn = new DQNode();
	dqn->setEventData(ev);
	addNode(dqn);
}

void EventDeque::addNode(DQNode *newNode){
	if (getFirstNode() == NULL || getFirstNode()->getEventTick() > newNode->getEventTick()){
		newNode->setNextNode(firstNode);
		firstNode = lastNode = newNode;
		tickIndex.insert(std::pair<int, DQNode*>(newNode->getEventTick(), newNode));
		size++;
		return;
	}
	DQNode* checkNode = getFirstNodeAtTick(newNode->getEventTick());
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

DQNode* EventDeque::getFirstNode(){
	return firstNode;
}

DQNode* EventDeque::getLastNode(){
	return lastNode;
}

DQNode* EventDeque::getFirstNodeAtTick(int tick){
	if (size<=0 || tickIndex.find(tick) == tickIndex.end()){
		return NULL;
	} 
	return tickIndex.find(tick)->second;	
}

DQNode* EventDeque::getLastNodeAtTick(int tick){
	if (size<=0 || tickIndex.find(tick) == tickIndex.end()){
		return NULL;
	}
	DQNode* startNode = tickIndex.find(tick)->second;
	while (startNode->getNextNode()->getEventTick() == tick){
		startNode = startNode->getNextNode();
	}

	return startNode;
}

EventDeque* EventDeque::getNodesBetween(int start, int end){
	DQNode* startNode = getFirstNodeAtTick(start);
	DQNode* endNode = getLastNodeAtTick(end);
	EventDeque* returnED = new EventDeque(startNode);
	
	while (startNode != endNode){
		startNode = startNode->getNextNode();
		returnED->addNode(startNode);
	}

	return returnED;
}

//hmm
void EventDeque::removeNode(DQNode *remNode){
	//manage the hash map
	if (getFirstNodeAtTick(remNode->getEventTick()) == remNode){ //if remNode is the one in the hash, remove it
		tickIndex.erase(remNode->getEventTick());
		if (size > 1 && remNode->getNextNode()->getEventTick() == remNode->getEventTick()){ 
			//and if the next node also equals remNode, add that node to the hash
			tickIndex.insert(std::pair<int, DQNode*>(remNode->getEventTick(), remNode->getNextNode()));
		}
	}
	//take care of the deque
	if (size > 1){
		if (remNode->getNextNode() != NULL) {remNode->getNextNode()->setPrevNode(remNode->getPrevNode());}
		if (remNode->getPrevNode() != NULL){remNode->getPrevNode()->setNextNode(remNode->getNextNode());}
	}
	if (remNode == getFirstNode()){
		firstNode = remNode->getNextNode();
	}
	if (remNode == getLastNode()){
		lastNode = remNode->getPrevNode();
	}
	size--;
}