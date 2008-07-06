/* Interfact with prop. */

#ifndef _INTERACT_H_
#define _INTERACT_H_

#include "event.h"
#include "item.h"

class InteractEvent : public Event {
	private:
		Entity* actor;
		Coord* loc;

	public:
		InteractEvent(Entity* _actor, Coord* _loc);
		Message* resolve();
};

#endif