#include "attack_event.h"

AttackEvent::AttackEvent(Entity* nAttacker, Entity* nDefender){
	setType(Event::ATTACK);
	setAttacker(nAttacker);
	setDefender(nDefender);
}

Entity* AttackEvent::getAttacker(){
	return attacker;
}

Entity* AttackEvent::getDefender(){
	return defender;
}

void AttackEvent::setAttacker(Entity* nAttacker){
	attacker = nAttacker;
}

void AttackEvent::setDefender(Entity *nDefender){
	defender = nDefender;
}

int AttackEvent::resolve(){
	//pretty much the code from referee, but to remove a dead entity, it'll add a REMOVE_ENT event to the queue
	return 10;
}