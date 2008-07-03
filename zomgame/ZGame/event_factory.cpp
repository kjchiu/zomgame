#include "event_factory.h"
#include "event_types.h"
Event* EventFactory::createAttackEvent(Entity* nAttacker, Entity* nDefender, int tick){
	AttackEvent* e = new AttackEvent(nAttacker, nDefender);
	e->setTick(tick);
	return e;
}

Event* EventFactory::createMoveEvent(Entity* nMover, MapBlock* nCurLoc, MapBlock* nDestLoc, int tick){
	return new MoveEvent(nMover, nCurLoc, nDestLoc);
}