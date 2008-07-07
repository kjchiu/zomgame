/* Represents a ranged attack in event form */

#ifndef _RANGED_ATTACH_E_H_
#define _RANGED_ATTACH_E_H_

#include "event.h"

class RangedAttackEvent : public Event {
	private:
		Player* player;
		Coord* targetLoc;

	public:
		RangedAttackEvent(Player* player, Coord* targetLoc);
		Entity* getAttacker();
		Coord* getTarget();
		Message* resolve();

};



#endif