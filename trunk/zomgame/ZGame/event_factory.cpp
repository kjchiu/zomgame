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

Event* EventFactory::createGetItemEvent(Entity* picker, Coord* loc, int index, int tick) {
	GetItemEvent *e = new GetItemEvent(picker, loc, index);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}

Event* EventFactory::createSpawnEntityEvent(Entity* spawner, Coord* loc, int tick){
	SpawnEntityEvent *e = new SpawnEntityEvent(spawner, loc);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}

Event* EventFactory::createSpawnItemEvent(Item* spawner, Coord* loc, int tick){
	SpawnItemEvent *e = new SpawnItemEvent(spawner, loc);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}

Event* EventFactory::createSpawnPropEvent(Prop *spawner, Coord *loc, int tick){
	SpawnPropEvent *e = new SpawnPropEvent(spawner, loc);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}

Event* EventFactory::createInteractEvent(Entity *actor, Coord *loc, int tick) {
	InteractEvent *e = new InteractEvent(actor, loc);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}