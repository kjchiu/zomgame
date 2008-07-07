/* An event that spawns an entity given a coordinate and an entity to spawn. */

#ifndef _SPAWN_P_H
#define _SPAWN_P_H

#include "event.h"
#include "coord.h"

class SpawnPropEvent : public Event{
	private:
		Prop* spawner;
		Coord* loc;

	public:
		SpawnPropEvent(Prop* nSpawner, Coord* nLoc);

		Message* resolve();
};

#endif