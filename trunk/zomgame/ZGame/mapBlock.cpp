#include "mapBlock.h"

MapBlock::MapBlock(){
	entityList = vector<Entity*>();
	propList = vector<Prop*>();
	terrain = new Wheat();
}

/* Adds an entity to the entities on the mapBlock, takes an int as well for height */
void MapBlock::addEntity(Entity *entity){
	//note, check for multiple entities on the same height. Something's wrong if that happens
	entityList.push_back(entity);
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
	} else if (!propList.empty()){
		return propList.back()->getDisplayChar();
	}
	return terrain->getDisplayChar();
}

/* Return the color for this tile of the map */
short MapBlock::getColor() {
	if (!entityList.empty()) {
		return entityList.back()->getColor();
	}
	return terrain->getColor();
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
	for (int i=0; i<propList.size(); i++){
		if (!propList.at(i)->isPassable()){
			return false;
		}
	}
	return true;
}

/* Remove an entity from the list. Might take height later, if necessary */
void MapBlock::removeEntity(Entity *entity){
	entityList.pop_back(); //change this
}

/* Remove an prop from the list. Might take height later, if necessary */
void MapBlock::removeProp(Prop *prop){
	propList.pop_back(); //I can't believe there is no remove function for vectors. wtf.
}

/* Set the terrain. For initializing or terrain modification (wall destruction, for example) */
void MapBlock::setTerrain(Terrain* ter){
	terrain = ter;
}