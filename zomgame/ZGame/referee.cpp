#include "referee.h"

Referee::Referee(Game* game){
	this->game = game;
	srand(0);
}


int Referee::resolveEvents(int currentTick, EventDeque* eventDeque){
	int numEvents = 0;
	DQNode* resolvedEvent;
	DQNode* currentEvent = eventDeque->getFirstNode();
	while (currentEvent != NULL && currentEvent->getEventTick() <= currentTick){
		Message* msg = currentEvent->getEventData()->resolve();
		if (msg){
			game->addMessage(msg);
		}
		resolvedEvent = currentEvent;
		currentEvent = currentEvent->getNextNode();
		eventDeque->removeNode(resolvedEvent);
		delete resolvedEvent;
		numEvents++;
	}
	return numEvents;
}
