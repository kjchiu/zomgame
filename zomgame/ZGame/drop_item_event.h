/* Dropping an item and placing it on the ground. */

#ifndef _DROP_ITEM_H_
#define _DROP_ITEM_H_

#include "event.h"
#include "item.h"

class DropItemEvent : public Event {
	private:
		Entity* actor;
		int index;

	public:
		DropItemEvent(Entity* actor, int index);
		Message* resolve();
};

#endif
