#include "dq_node.h"

DQNode::DQNode(){
	init(NULL, NULL);
}

DQNode::DQNode(DQNode *nPrevNode){
	init(nPrevNode, NULL);
}

DQNode::DQNode(DQNode *nPrevNode, DQNode *nNextNode){
	init(nPrevNode, nNextNode);
}

DQNode::~DQNode(){
	delete eventData;
}

void DQNode::init(DQNode* nPrevNode, DQNode* nNextNode){
	setPrevNode(nPrevNode);
	setNextNode(nNextNode);
	//set the data here
}

Event* DQNode::getEventData(){
	return eventData;
}

int DQNode::getEventTick(){
	return eventData->getTick();
}

DQNode* DQNode::getNextNode(){
	return nextNode;
}

DQNode* DQNode::getPrevNode(){
	return prevNode;
}

void DQNode::setEventData(Event* nEventData){
	eventData = nEventData;
}

void DQNode::setNextNode(DQNode* nNextNode){
	nextNode = nNextNode;
}

void DQNode::setPrevNode(DQNode* nPrevNode){
	prevNode = nPrevNode;
}