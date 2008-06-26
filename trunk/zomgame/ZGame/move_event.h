/* Represents a move from one square to another. Checks for obstacles. */

#ifndef _MOVE_E_H
#define _MOVE_E_H

#include "event.h"
#include "mapblock.h"

class MoveEvent : public Event {
	private:
		Entity* mover;
		MapBlock* currentLoc;
		MapBlock* destinationLoc;

	public:
		MoveEvent();
		MoveEvent(Entity* nMover, MapBlock* curLoc, MapBlock* destLoc);
		
		Message* resolve();
};

#endif