/* Represents a move from one square to another. Checks for obstacles. */

#ifndef _MOVE_E_H
#define _MOVE_E_H

#include "event.h"
#include "mapblock.h"
#include "entity.h"

class MoveEvent : public Event {
	private:
		Entity* mover;
		Coord* destinationLoc;

	public:
		MoveEvent();
		MoveEvent(Entity* nMover, Coord* destLoc);
		
		Message* resolve();
};

#endif