#include "move_event.h"

MoveEvent::MoveEvent(){
	setType(Event::MOVE);
}

MoveEvent::MoveEvent(Entity *nMover, MapBlock *curLoc, MapBlock *destLoc){
	setType(Event::MOVE);
	mover = nMover;
	currentLoc = curLoc;
	destinationLoc = destLoc;
}

Message* MoveEvent::resolve(){
	if (destinationLoc->hasEntities()){
		addEvent(EventFactory::createAttackEvent(mover, checkBlock->getTopEntity(), getTick());
	} 

	return new Message();
}