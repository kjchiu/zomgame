/* Represents an attack in event form */

#ifndef _ATTACK_E_H
#define _ATTACK_E_H

#include "event.h"

class AttackEvent : public Event {
	private:
		Entity* attacker;
		Entity* defender;

	public:
		AttackEvent(Entity* nAttacker, Entity* nDefender);
		Entity* getAttacker();
		Entity* getDefender();
		void setAttacker(Entity* nAttacker);
		void setDefender(Entity* nDefender);

		Message* resolve();

};



#endif