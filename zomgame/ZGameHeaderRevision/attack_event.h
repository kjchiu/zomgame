/* Represents an attack in event form */

#ifndef _ATTACK_E_H
#define _ATTACK_E_H

#include "all_includes.h"

class AttackEvent : public Event {
	private:
		Entity* attacker;
		Coord* targetLoc;

	public:
		AttackEvent(Entity* nAttacker, Coord* targetLoc);
		Entity* getAttacker();
		Coord* getTarget();
		Message* resolve();

};



#endif