#include "event_factory.h"

AttackEvent* EventFactory::createAttackEvent(Entity* nAttacker, Entity* nDefender, int tick){
	AttackEvent* e = new AttackEvent(nAttacker, nDefender);
	e->setTick(tick);
	return e;
}

MoveEvent* EventFactory::createMoveEvent(Entity* nMover, MapBlock* nCurLoc, MapBlock* nDestLoc, int tick){
	return new MoveEvent();
}