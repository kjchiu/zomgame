/* Produces events */

#ifndef _EVENT_FAC_H
#define _EVENT_FAC_H

#include "entity.h"
#include "mapblock.h"


class EventFactory;
class Event;


class EventFactory {
	private:
	public:
		static Event* createAttackEvent(Entity* nAttacker, Entity* nDefender, int tick);
		static Event* createMoveEvent(Entity* mover, MapBlock* curLoc, MapBlock* destLoc, int tick);
};

#endif