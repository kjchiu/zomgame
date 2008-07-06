#include "spawn_item_event.h"
#include "game.h"

SpawnItemEvent::SpawnItemEvent(Item* item, Coord* nLoc) : loc(nLoc), Event(SPAWN_ITEM){
	items.push_back(item);
}

SpawnItemEvent::SpawnItemEvent(std::vector<Item*> &_items, Coord* _loc)
: items(_items), loc(_loc), Event(SPAWN_ITEM) {
}

Message* SpawnItemEvent::resolve(){
	if (Game::getInstance()->getMap()->isWithinMap(loc)){
		for (int i = 0; i < items.size(); i++) {
		Game::getInstance()->getMap()->getBlockAt(loc)->addItem(items.at(i)); 
		}
	} 
	return NULL;
}