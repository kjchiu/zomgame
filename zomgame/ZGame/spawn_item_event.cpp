#include "spawn_item_event.h"
#include "game.h"

SpawnItemEvent::SpawnItemEvent(Item* nSpawn, Coord* nLoc):Event(SPAWN_ITEM){
	spawner = nSpawn;
	loc = nLoc;
}

Message* SpawnItemEvent::resolve(){
	if (!Game::getInstance()->getMap()->isWithinMap(loc)){
		return NULL;
	}
	
//	then what?
//	if (Game::getInstance()->getMap()->getBlockAt(loc)->hasEntities()){
//		return NULL;
//	}

	Game::getInstance()->getMap()->getBlockAt(loc)->addItem(spawner); 
	return NULL;
}