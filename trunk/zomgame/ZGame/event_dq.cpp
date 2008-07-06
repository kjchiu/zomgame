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
	if (ev) {
		DQNode* dqn = new DQNode();
		dqn->setEventData(ev);
		addNode(dqn);
	}
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
	unsigned int i = 0;
	// does the keyframe exist?
	if (checkNode == NULL){
		
		tickIndex.insert(std::pair<int, DQNode*>(newNode->getEventTick(), newNode));
		while(i < keyframes.size()) {
			if (newNode->getEventTick() < keyframes.at(i)) {
				keyframes.insert(keyframes.begin() + i, newNode->getEventTick());
				break;
			}
			i++;
		}
	} else {
		// find last node in that queue;
		while(i < keyframes.size()) {
			if (newNode->getEventTick() < keyframes.at(i)) {
				break;
			} else {
				i++;
			}
		}
	}
	
	// i now holds the index of the current keyframe

	if (i + 1 >= keyframes.size()) {
		checkNode = lastNode;
	} else {
		checkNode = getFirstNodeAtTick(keyframes.at(i+1));
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
	if (size == 0 || tickIndex.find(tick) == tickIndex.end()){
		return NULL;
	} 
	return tickIndex.find(tick)->second;	
}

DQNode* EventDeque::getLastNodeAtTick(int tick){
	unsigned int i = 0;
	while(i < keyframes.size()) {
		if (tick < keyframes.at(i)) {
			break;
		}
		i++;
	}
	
	if (i + 1 > keyframes.size()) {
		return lastNode;
	} else {
		return getFirstNodeAtTick(keyframes.at(i+1))->getPrevNode();
	}
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

int EventDeque::getSize(){
	return size;
}

void EventDeque::removeNode(DQNode *remNode){
	//manage the hash map
	if (getFirstNodeAtTick(remNode->getEventTick()) == remNode){ //if remNode is the one in the hash, remove it
		tickIndex.erase(remNode->getEventTick());
		// if more events exist in that tick
		if (remNode->getNextNode() &&
			remNode->getNextNode()->getEventTick() == remNode->getEventTick()) {
			tickIndex.insert(std::pair<int,DQNode*>(remNode->getEventTick(), remNode->getNextNode()));
		}
	}

	//take care of the deque
	if (size > 1){
		if (remNode->getNextNode() != NULL) {remNode->getNextNode()->setPrevNode(remNode->getPrevNode());}
		if (remNode->getPrevNode() != NULL){remNode->getPrevNode()->setNextNode(remNode->getNextNode());}
	}
	if (remNode == getFirstNode()) {
		firstNode = remNode->getNextNode();
	}
	if (remNode == getLastNode()) {
		lastNode = remNode->getPrevNode();
	}
	size--;
}