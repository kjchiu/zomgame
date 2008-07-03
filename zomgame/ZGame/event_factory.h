/* Produces events */

#ifndef _EVENT_FAC_H
#define _EVENT_FAC_H

#include "entity.h"
#include "mapblock.h"
#include "direction.h"

class EventFactory;
class Event;

class EventFactory {
	private:
	public:

		// NOTE: all tick parameters are offsets from the current tick	
		static Event* createAttackEvent(Entity* attacker, Direction dir, int tick);
		static Event* createAttackEvent(Entity* attacker, Coord* targetLoc, int tick);
		
		static Event* createMoveEvent(Entity* mover, Direction dir, int tick);
};

#endif