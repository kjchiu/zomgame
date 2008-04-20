#include "map.h"

Map::Map(){
	// Clear the CHAR_INFO buffer:
    for (int i=0; i<MAPWIDTH*MAPHEIGHT; ++i) {
        map[i] = new MapBlock(); //fill the map with blank areas
	}

	for (int i=0; i<MAPWIDTH*MAPHEIGHT; ++i) {
       viewMap[i].Char.UnicodeChar = ' ';
        viewMap[i].Attributes = 
            BACKGROUND_BLUE
            |BACKGROUND_GREEN
            |BACKGROUND_RED
            |BACKGROUND_INTENSITY;
    }
}

void Map::clear() {
	for (int i=0; i<MAPWIDTH*MAPHEIGHT; i++) {  // Yes, so clear the buffer to spaces:
		
	}
}

void Map::drawMenu(){
	for (int i = 0; i < MAPHEIGHT; i++){
		setCharAt('|', MAPWIDTH-15, i);
	}
	/*setCharAt('-', MAPWIDTH-14, 15);
	setCharAt('-', MAPWIDTH-13, 15);
	setCharAt('-', MAPWIDTH-12, 15);
	setCharAt('-', MAPWIDTH-11, 15);
	setCharAt('-', MAPWIDTH-10, 15);
	setCharAt('-', MAPWIDTH-9, 15);
	setCharAt('-', MAPWIDTH-8, 15);
	setCharAt('-', MAPWIDTH-7, 15);
	setCharAt('-', MAPWIDTH-6, 15);
	setCharAt('-', MAPWIDTH-5, 15);
	setCharAt('-', MAPWIDTH-4, 15);
	setCharAt('-', MAPWIDTH-3, 15);
	setCharAt('-', MAPWIDTH-2, 15);
	setCharAt('-', MAPWIDTH-1, 15);*/
}

char Map::getCharAt(int x, int y) {
	return map[x + (y * MAPWIDTH)]->getChar();
}

MapBlock* Map::getMap() {
	return *map;
}

CHAR_INFO* Map::getViewableMap(int pX, int pY) {
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
				if (viewMap[i + (j * VIEWWIDTH)].Char.UnicodeChar != '.'){
					int y = 1;
				}
			}
		}
	}
	return viewMap;
}

void Map::setCharAt(char setChar, int x, int y){
//	 map[x + (y * MAPWIDTH)].Char.UnicodeChar = setChar;
}

void Map::draw(){

}