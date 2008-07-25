#include "event_types.h"
#include "event_factory.h"
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
	MapBlock *block = Game::getInstance()->getMap()->getBlockAt(targetLoc);
	if (block->hasEntities() || block->hasProps()) {
		AttackEvent *e = new AttackEvent(attacker, targetLoc);
		e->setTick(Game::getInstance()->getTickcount() + tick);
		return e;
	} else {
		return NULL;
	}
	
}

Event* EventFactory::createRangedAttackEvent(Player* player, Coord* targetLoc, int tick) {
	RangedAttackEvent *e = new RangedAttackEvent(player, targetLoc);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}

Event* EventFactory::createDamageEntityEvent(Entity* entity, int damage, int tick){
	DamageEntityEvent *e = new DamageEntityEvent(entity, damage);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}

Event* EventFactory::createGetItemEvent(Entity* picker, Coord* loc, int index, int tick) {
	GetItemEvent *e = new GetItemEvent(picker, loc, index);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}

Event* EventFactory::createDropItemEvent(Entity* actor, int index, int tick) {
	DropItemEvent *e = new DropItemEvent(actor, index);
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

Event* EventFactory::createSpawnItemEvent(std::vector<Item*> items, Coord* loc, int tick) {
	SpawnItemEvent *e = new SpawnItemEvent(items, loc);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}

Event* EventFactory::createSpawnPropEvent(Prop *spawner, Coord *loc, int tick){
	SpawnPropEvent *e = new SpawnPropEvent(spawner, loc);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}

Event* EventFactory::createInteractEvent(Entity *actor, Coord *loc, int tick) {
	if (Game::getInstance()->getMap()->getBlockAt(loc)->hasProps()) {
		InteractEvent *e = new InteractEvent(actor, loc);
		e->setTick(Game::getInstance()->getTickcount() + tick);
		return e;
	} else {
		return NULL;
	}
}

Event* EventFactory::createSkillEvent(Entity *actor, Skill *skill, void* target, int tick) {
	SkillEvent *e = new SkillEvent(actor, skill, target);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}

Event* EventFactory::createAddEffectEvent(Entity* target, Effect* effect, int tick) {
	EventAddEffect *e = new EventAddEffect(target, effect);
	e->setTick(Game::getInstance()->getTickcount() + tick);
	return e;
}