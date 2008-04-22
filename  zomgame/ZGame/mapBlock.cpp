#include "mapBlock.h"

MapBlock::MapBlock(){
	terrain = '.';
}

char MapBlock::getChar() {
	//if itemArray is not empty, return the first item's char. Will also get color in other function. Otherwise...
	return terrain;
}

void MapBlock::setTerrain(char ter){
	terrain = ter;
}