#include "event.h"

Event::Event(){
	tick = 0;
}

int Event::getTick(){
	return tick;
}

void Event::setTick(int nTick){
	tick = nTick;
}