#include "event.h"

int Event::id = 0;

Event::Event(){
	tick = 0;
	thisID = id++;
}

int Event::getType(){
	return eventType;
}

int Event::getTick(){
	return tick;
}

void Event::setTick(int nTick){
	tick = nTick;
}

void Event::setType(EventType nEventType){
	eventType = nEventType;
}