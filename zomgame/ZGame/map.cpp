#include "map.h"

Map::Map(){
	height = MAPHEIGHT;
	width = MAPWIDTH;
	for (int i=0; i<height*width; ++i) {
        map[i] = new MapBlock(); //fill the map with blank areas
	}
}

void Map::clear() {
	for (int i=0; i<height*width; i++) {  // clear the map to new MapBlocks:
		map[i] = new MapBlock();
	}
}

MapBlock* Map::getBlockAt(int x, int y){
	return map[x + (y * getWidth())];
}

MapBlock* Map::getBlockAt(Coord *coord) {
	return map[coord->getX() + (coord->getY() * getWidth())];
}

char Map::getCharAt(int x, int y) {
	return map[x + (y * getWidth())]->getChar();
}

int Map::getHeight(){
	return height;
}

int Map::getWidth(){
	return width;
}

MapBlock* Map::getMap() {
	return *map;
}

void Map::setBlockAt(MapBlock* mBlock, int x, int y){
	 map[x + (y * getWidth())] = mBlock;	
}

void Map::draw(){

}