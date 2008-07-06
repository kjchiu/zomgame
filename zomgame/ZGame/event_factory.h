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
	
		static Event* createGetItemEvent(Entity* picker, Coord* loc, int index, int tick);

		static Event* createMoveEvent(Entity* mover, Direction dir, int tick);

		static Event* createSpawnEntityEvent(Entity* spawner, Coord* loc, int tick);
		static Event* createSpawnItemEvent(Item* spawner, Coord* loc, int tick);
		static Event* createSpawnPropEvent(Prop* spawner, Coord* loc, int tick);

		static Event* createInteractEvent(Entity* actor, Coord* loc, int tick);

};

#endif