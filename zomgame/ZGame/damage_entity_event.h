/* Reducing an entity's health */

#ifndef _DAMAGE_ENTITY_H_
#define _DAMAGE_ENTITY_H_

#include "event.h"
#include "entity.h"

class DamageEntityEvent : public Event {
	private:
		Entity* entity;
		int damage;

	public:
		DamageEntityEvent(Entity* nEntity, int nDamage);
		int getDamage();
		Entity* getEntity();
		Message* resolve();
};

#endif
