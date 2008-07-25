#include "map.h"
#include "zombie.h"
#include <ctime> //for debugging. used to generate shit random maps
#include <fstream>

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
		if(map[i])
		{
			delete map[i];
			map[i] = NULL;
		}
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

void Map::makeRoadAt(Coord* topLeft, int width, int height){
	Coord* newCoord = new Coord();
	for (int x=topLeft->getX(); x<topLeft->getX()+width;x++){
		for (int y=topLeft->getY(); y<topLeft->getY()+height;y++){
			newCoord->setX(x);
			newCoord->setY(y);
			if (isWithinMap(newCoord)){
				if (rand() % 3 > 0){
					getBlockAt(newCoord)->setTerrain(TerrainFactory::makeTerrain(ROAD));	
				}
			}
		}
	}
}

void Map::makeRoomAt(Coord* topLeft, int width, int height){
	Coord* newCoord = new Coord();
	for (int x=topLeft->getX(); x<topLeft->getX()+width;x++){
		for (int y=topLeft->getY(); y<topLeft->getY()+height;y++){
			newCoord->setX(x);
			newCoord->setY(y);
			if (isWithinMap(newCoord)){
				getBlockAt(newCoord)->clear();
				getBlockAt(newCoord)->setTerrain(new IndoorTile());		//put down the floor
				if ((x == topLeft->getX() || x == topLeft->getX() + width-1) || //put up the walls
					(y == topLeft->getY() || y == topLeft->getY() + height-1)){	
						getBlockAt(newCoord)->addProp(PropFactory::createWall());
				}
			}
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

void Map::loadFrom(const char* filename)
{
	//this could fail badly
	try
	{
		//open the file
		ifstream in(filename, ios::in | ios::binary);

		//read the identifier
		char ident[4];
		in.read(ident, 4);

		//verify the file type
		if((ident[0] != 'Z') || (ident[1] != 'M'))
			return;
		int version = (ident[2] << 8) + ident[3];
		if(version != 1)
			return;

		//read in the size
		in.read(reinterpret_cast<char*>(&width), sizeof(int));
		in.read(reinterpret_cast<char *>(&height), sizeof(int));

		//read in the grid
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				getBlockAt(x, y)->loadFrom(in);
			}
		}

		//read in the metadata
		in.seekg(-static_cast<int>(sizeof(int)), ios::end);
		int metaSize = 0;
		in.read(reinterpret_cast<char*>(&metaSize), sizeof(int));
		char *metadata = new char[metaSize];
		in.seekg(-(static_cast<int>(sizeof(int)) + metaSize), ios::end);
		in.read(metadata, metaSize);
		//do something with metadata before deleting it
		delete[] metadata;

		//close the file
		in.close();
	}
	catch(...)
	{
		//wtf do I do with this? printf?
	}
}

void Map::saveTo(const char* filename)
{
	//this could fail badly
	try
	{
		//open the file
		ofstream out(filename, ios::out | ios::binary);

		//write out the identifier
		char ident[4] = {'Z', 'M', 0, 1};
		out.write(ident, 4);

		//write out the size
		out.write(reinterpret_cast<char *>(&width), sizeof(int));
		out.write(reinterpret_cast<char *>(&height), sizeof(int));

		//write out the grid
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				getBlockAt(x, y)->saveTo(out);
			}
		}

		//write out the metadata
		char *meta = "This should be metadata.";
		int metaLen = 25;
		out.write(meta, metaLen);
		out.write(reinterpret_cast<char *>(&metaLen), sizeof(int));

		//close the file
		out.close();
	}
	catch(...)
	{
		// something should go here
	}
}