/* An event that spawns an entity given a coordinate and an entity to spawn. */

#ifndef _SPAWN_E_H
#define _SPAWN_E_H

#include "event.h"
#include "coord.h"

class SpawnEntityEvent : public Event{
	private:
		Entity* spawner;
		Coord* loc;

	public:
		SpawnEntityEvent(Entity* nSpawner, Coord* nLoc);

		Message* resolve();
};

#endif