#include "event_factory.h"
#include "event_types.h"
#include "game.h"



Event* EventFactory::createMoveEvent(Entity* mover, Direction dir, int tick) {
	Coord* targetLoc = new Coord();
	*targetLoc = *mover->getLoc() + dir;
	MoveEvent *e = new MoveEvent(mover, targetLoc);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;

}

Event* EventFactory::createAttackEvent(Entity* attacker, Direction dir, int tick) {
	Coord* targetLoc = new Coord();
	*targetLoc = *attacker->getLoc() + dir;
	return EventFactory::createAttackEvent(attacker, targetLoc, tick);
}

Event* EventFactory::createAttackEvent(Entity* attacker, Coord* targetLoc, int tick) {
	AttackEvent *e = new AttackEvent(attacker, targetLoc);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}