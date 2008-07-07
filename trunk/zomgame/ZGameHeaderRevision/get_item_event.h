/* Picking up an item and placing it in the inventory. */

#ifndef _GET_ITEM_H
#define _GET_ITEM_H

#include "event.h"
#include "item.h"

class GetItemEvent : public Event {
	private:
		Entity* picker;
		Coord* loc;
		int index;

	public:
		GetItemEvent(Entity* nPicker, Coord* nLoc, int nIndex);
		Message* resolve();
};

#endif
