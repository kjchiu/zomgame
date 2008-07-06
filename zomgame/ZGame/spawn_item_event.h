/* An event that spawns an entity given a coordinate and an entity to spawn. */

#ifndef _SPAWN_I_H
#define _SPAWN_I_H

#include "event.h"
#include "coord.h"
#include <vector>

class SpawnItemEvent : public Event{
	private:
		std::vector<Item*> items;
		Coord* loc;

	public:
		SpawnItemEvent(Item* item, Coord* nLoc);
		SpawnItemEvent(std::vector<Item*> &items, Coord* loc);
		Message* resolve();
};

#endif