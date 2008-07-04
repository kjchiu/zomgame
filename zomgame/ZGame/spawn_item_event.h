/* An event that spawns an entity given a coordinate and an entity to spawn. */

#ifndef _SPAWN_I_H
#define _SPAWN_I_H

#include "event.h"
#include "coord.h"

class SpawnItemEvent : public Event{
	private:
		Item* spawner;
		Coord* loc;

	public:
		SpawnItemEvent(Item* nSpawner, Coord* nLoc);

		Message* resolve();
};

#endif