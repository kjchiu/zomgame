#include "map.h"

Map::Map(){
	// Clear the CHAR_INFO buffer:
    for (int i=0; i<MAPWIDTH*MAPHEIGHT; ++i) {
        map[i] = new MapBlock(); //fill the map with blank areas
	}

	/*for (int i=0; i<MAPWIDTH*MAPHEIGHT; ++i) {
       viewMap[i].Char.UnicodeChar = ' ';
        viewMap[i].Attributes = 
            BACKGROUND_BLUE
            |BACKGROUND_GREEN
            |BACKGROUND_RED
            |BACKGROUND_INTENSITY;
    }*/
}

void Map::clear() {
	for (int i=0; i<MAPWIDTH*MAPHEIGHT; i++) {  // clear the map to new MapBlocks:
		map[i] = new MapBlock();
	}
}

MapBlock* Map::getBlockAt(int x, int y){
	return map[x + (y * MAPWIDTH)];
}

char Map::getCharAt(int x, int y) {
	return map[x + (y * MAPWIDTH)]->getChar();
}

MapBlock* Map::getMap() {
	return *map;
}

/*CHAR_INFO* Map::getViewableMap(int pX, int pY) {
	viewMap[VIEWWIDTH/2 + (VIEWHEIGHT/2 * MAPWIDTH)].Char.UnicodeChar = '@';
	//viewmap(x,y) = map(playerX-halfway+x, playerY-halfway+y)
	for (int i=0; i<VIEWWIDTH; i++){
		for (int j=0; j<VIEWHEIGHT; j++){
			int mapX = pX - VIEWWIDTH/2 + i;  //x position on the map
			int mapY = pY - VIEWHEIGHT/2 + j; //y position on the map 
			if (mapX < 0 || mapX > MAPWIDTH - 1 || mapY < 0 || mapY > MAPHEIGHT - 1){
				viewMap[i + (j * VIEWWIDTH)].Char.UnicodeChar = '-';
			} else {
				viewMap[i + (j * VIEWWIDTH)].Char.UnicodeChar = this->getCharAt(mapX, mapY); 
			}
		}
	}
	return viewMap;
}*/

void Map::setCharAt(char setChar, int x, int y){
//	 map[x + (y * MAPWIDTH)].Char.UnicodeChar = setChar;
}

void Map::setBlockAt(MapBlock mBlock, int x, int y){
	MapBlock* mB = &mBlock;
	
	 map[x + (y * MAPWIDTH)] = mB;
	
}

void Map::draw(){

}