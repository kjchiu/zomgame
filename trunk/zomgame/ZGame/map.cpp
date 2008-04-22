#include "map.h"

Map::Map(){
	for (int i=0; i<MAPWIDTH*MAPHEIGHT; ++i) {
        map[i] = new MapBlock(); //fill the map with blank areas
	}
}

void Map::clear() {
	for (int i=0; i<MAPWIDTH*MAPHEIGHT; i++) {  // clear the map to new MapBlocks:
		map[i] = new MapBlock();
	}
}

MapBlock* Map::getBlockAt(int x, int y){
	return map[x + (y * MAPWIDTH)];
}

MapBlock* Map::getBlockAt(Coord *coord) {
	return map[coord->getX() + (coord->getY() * MAPWIDTH)];
}

char Map::getCharAt(int x, int y) {
	return map[x + (y * MAPWIDTH)]->getChar();
}

MapBlock* Map::getMap() {
	return *map;
}

void Map::setCharAt(char setChar, int x, int y){
//	 map[x + (y * MAPWIDTH)].Char.UnicodeChar = setChar;
}

void Map::setBlockAt(MapBlock* mBlock, int x, int y){
	 map[x + (y * MAPWIDTH)] = mBlock;	
}

void Map::draw(){

}