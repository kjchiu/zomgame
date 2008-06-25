#include "event_factory.h"

AttackEvent* EventFactory::createAttackEvent(Entity* nAttacker, Entity* nDefender, int tick){
	return new AttackEvent(nAttacker, nDefender, tick);
}