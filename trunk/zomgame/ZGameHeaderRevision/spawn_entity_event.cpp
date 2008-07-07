#include "spawn_entity_event.h"
#include "game.h"

SpawnEntityEvent::SpawnEntityEvent(Entity* nSpawn, Coord* nLoc):Event(SPAWN_ENT){
	spawner = nSpawn;
	loc = nLoc;
}

Message* SpawnEntityEvent::resolve(){
	if (!Game::getInstance()->getMap()->isWithinMap(loc)){
		return NULL;
	}
	//what happens if there's a prop/entity on the spawn location? Telefrag?
	
	spawner->setLoc(loc);
	Game::getInstance()->getMap()->getBlockAt(loc)->addEntity(spawner); 
	
	return NULL;
}