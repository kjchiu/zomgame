#include "mapBlock.h"

MapBlock::MapBlock(){
	entityList = vector<Entity*>();
	propList = vector<Prop*>();
	itemList = vector<Item*>();
	terrain = new Grass();
}

/* Adds an entity to the entities on the mapBlock, takes an int as well for height */
void MapBlock::addEntity(Entity *entity){
	//note, check for multiple entities on the same height. Something's wrong if that happens
	entityList.push_back(entity);
}

void MapBlock::addItem(Item* item){
	itemList.push_back(item);
}

/* Adds a prop to the mapBlock */
void MapBlock::addProp(Prop* prop){
	propList.push_back(prop);
}

/* Gets the char that represents this tile of the map */
chtype MapBlock::getChar() {
	//order of appearance -> entity, item, prop, terrain
	if (!entityList.empty()){
		return entityList.back()->getDisplayChar();
	} else if (!itemList.empty()){
		return itemList.back()->getDisplayChar();
	} else if (!propList.empty()){
		return propList.back()->getDisplayChar();
	}
	return terrain->getDisplayChar();
}

/* Return the color for this tile of the map */
short MapBlock::getColor() {
	if (!entityList.empty()) {
		return entityList.back()->getColor();
	} else if (!itemList.empty()){
		return itemList.back()->getColor();
	} else if (!propList.empty()){
		return propList.back()->getColor();
	}
	return terrain->getColor();
}

Item* MapBlock::getItemAt(int index){
	return itemList.back();
}

vector<Item*> MapBlock::getItems() {
	return itemList;
}

/* Simply get the entity that's on the top of the vector/stack. */
Entity* MapBlock::getTopEntity(){
	return entityList.back();	
}

/* Are there any creatures here? Take an int, change with hasEntitiesAt(int height) eventually */
bool MapBlock::hasEntities(){
	return !entityList.empty();
}

/* Check for entities, other stuff */
bool MapBlock::isPassable(){
	if (!entityList.empty()) {
		return false;	
	}
	for (unsigned int i=0; i<propList.size(); i++){
		if (!propList.at(i)->isPassable()){
			return false;
		}
	}
	return true;
}

// @TODO WHEN HEIGHT IS IMPLEMENTED, ONLY CHECK AT THE HEIGHT
/* Remove an entity from the list. Might take height later, if necessary */
void MapBlock::removeEntity(Entity *entity){
	for (unsigned int i=0; i<entityList.size(); i++){
		if (entityList.at(i)->getID() == entity->getID()){
			if (i==entityList.size()-1){
				entityList.pop_back();
			} else {
				entityList.erase(entityList.begin()+i, entityList.begin()+i+1); 
			} 
		}
	}
}

void MapBlock::removeItem(Item* item){
	for (unsigned int i=0; i<itemList.size(); i++){
		if (itemList.at(i)->getID() == item->getID()){
			if (i==itemList.size()-1){
				itemList.pop_back();
			} else {
				itemList.erase(itemList.begin()+i, itemList.begin()+i+1); 
			} 
		}
	}
}

/* Remove an prop from the list. Might take height later, if necessary */
void MapBlock::removeProp(Prop *prop){
	for (unsigned int i=0; i<propList.size(); i++){
		if (propList.at(i)->getID() == prop->getID()){
			if (i==propList.size()-1){
				propList.pop_back();
			} else {
				propList.erase(propList.begin()+i, propList.begin()+i+1); 
			} 
		}
	}
}

/* Set the terrain. For initializing or terrain modification (wall destruction, for example) */
void MapBlock::setTerrain(Terrain* ter){
	terrain = ter;
}