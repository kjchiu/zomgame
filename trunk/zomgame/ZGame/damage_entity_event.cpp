#include "damage_entity_event.h"

DamageEntityEvent::DamageEntityEvent(Entity* nEntity, int nDamage): Event(DMG_ENT){
	entity = nEntity;
	damage = nDamage;
}

Entity* DamageEntityEvent::getEntity(){
	return entity;
}

int DamageEntityEvent::getDamage(){
	return damage;
}

Message* DamageEntityEvent::resolve(){
	if (damage < 0){
		entity->getHealth()->changeCurValueBy(damage);
		return NULL; 
	} 
	
	entity->getHealth()->changeCurValueBy(-damage);
	return NULL;
}