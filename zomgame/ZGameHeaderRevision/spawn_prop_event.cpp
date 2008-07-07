#include "spawn_prop_event.h"
#include "game.h"

SpawnPropEvent::SpawnPropEvent(Prop* nSpawn, Coord* nLoc):Event(SPAWN_PROP){
	spawner = nSpawn;
	loc = nLoc;
}

Message* SpawnPropEvent::resolve(){
	if (!Game::getInstance()->getMap()->isWithinMap(loc)){
		return NULL;
	}
	
//	then what?
//	if (Game::getInstance()->getMap()->getBlockAt(loc)->hasEntities()){
//		return NULL;
//	}

	Game::getInstance()->getMap()->getBlockAt(loc)->addProp(spawner); 
	return NULL;
}