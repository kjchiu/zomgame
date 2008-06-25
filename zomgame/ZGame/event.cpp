#include "event.h"

Event::Event(){
	tick = 0;
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