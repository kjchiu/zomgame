#include "mapBlock.h"

MapBlock::MapBlock(){
	terrain = '.';
}

void MapBlock::addEntity(Entity *entity){
	entityList.push_back(entity);
}

char MapBlock::getChar() {
	//if itemArray is not empty, return the first item's char. Will also get color in other function. Otherwise...
	if (!entityList.empty()){
		return entityList.back()->getDisplayChar();
	}
	return terrain;
}

bool MapBlock::isPassable(){
	if (!entityList.empty()) {
		return false;	
	}

	return true;
}

void MapBlock::removeEntity(Entity *entity){
	//remove the entity given from the entity list
}

void MapBlock::setTerrain(char ter){
	terrain = ter;
}