#include "map.h"
#include "zombie.h"
#include <ctime> //for debugging. used to generate shit random maps

Map::Map(){
	height = MAPHEIGHT;
	width = MAPWIDTH;
	for (int i=0; i<height*width; ++i) {		
        map[i] = new MapBlock(); //fill the map with blank areas
		if (rand() % 10 > 8) {
		//	map[i]->addEntity(new Zombie());
		}
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

chtype Map::getCharAt(int x, int y) {
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

void Map::makeRoomAt(Coord* topLeft, int width, int height){
	Coord* newCoord = new Coord();
	for (int x=topLeft->getX(); x<topLeft->getX()+width;x++){
		for (int y=topLeft->getY(); y<topLeft->getY()+height;y++){
			if ((x == topLeft->getX() || x == topLeft->getX() + width-1) ||
				(y == topLeft->getY() || y == topLeft->getY() + height-1)){
				newCoord->setX(x);
				newCoord->setY(y);
				if (isWithinMap(newCoord)){
					getBlockAt(newCoord)->addProp(PropFactory::createWall());
				}
			} 
			getBlockAt(x, y)->setTerrain(new IndoorTile());
		}
	}
	getBlockAt(topLeft->getX(), topLeft->getY() + height/2)->removeProp(getBlockAt(topLeft->getX(), topLeft->getY() + height/2)->getTopProp());
	getBlockAt(topLeft->getX(), topLeft->getY() + height/2)->addProp(PropFactory::createDoor());

}

void Map::setBlockAt(MapBlock* mBlock, int x, int y){
	 map[x + (y * getWidth())] = mBlock;	
}

bool Map::isWithinMap(Coord* checkCoord){
	if (checkCoord->getX() < 0 || checkCoord->getY() < 0 || 
		checkCoord->getX() >= getWidth() || checkCoord->getY() >= getHeight()){
		return false; //can't move here, outside of map
	}
	return true;
}

void Map::draw(){

}