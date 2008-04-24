#include "mapBlock.h"

MapBlock::MapBlock(){
	terrain = new Wheat();
}

void MapBlock::addEntity(Entity *entity){
	entityList.push_back(entity);
}

char MapBlock::getChar() {
	//if itemArray is not empty, return the first item's char. Will also get color in other function. Otherwise...
	if (!entityList.empty()){
		return entityList.back()->getDisplayChar();
	}
	return terrain->getChar();
}

short MapBlock::getColor() {
	//return 
	if (!entityList.empty()) {
		return entityList.back()->getColor();
	}
	return terrain->getColor();
}

bool MapBlock::hasEntities(){
	return !entityList.empty();
}

bool MapBlock::isPassable(){
	if (!entityList.empty()) {
		return false;	
	}

	return true;
}

void MapBlock::removeEntity(Entity *entity){
	entityList.pop_back();

}

void MapBlock::setTerrain(Terrain* ter){
	terrain = ter;
}