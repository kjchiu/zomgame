/* This is a map, basically a wrapper class for the world, an array of MapBlocks */

#ifndef MAP
#define MAP

#include <stdlib.h>
#include <stdio.h>
#include "mapBlock.h"
#include "coord.h"
#include "terrain_factory.h"


class Map{
	private:	
		static const int MAPWIDTH = 100, MAPHEIGHT = 100;
		int height, width;

		MapBlock* map[MAPWIDTH*MAPHEIGHT];	//this is essentially the entire 'world'
		
	public:
		Map();
		void clear();
		void draw();
		MapBlock* getBlockAt(int x, int y);
		MapBlock* getBlockAt(Coord* coord);
		chtype getCharAt(int x, int y);
		MapBlock* getMap();
		int getHeight();
		int getWidth();
		void makeRoomAt(Coord* topLeft, int width, int height); //makes a room. I'm bored.
		void makeRoadAt(Coord* topLeft, int width, int height);
		void setBlockAt(MapBlock *mBlock, int x, int y);
		bool isWithinMap(Coord* checkCoord);
		void loadFrom(const char* filename);
		void saveTo(const char* filename);
		

};

#endif