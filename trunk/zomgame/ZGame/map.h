/* This is a map, basically a wrapper class for the world, an array of MapBlocks */
#ifndef MAP
#define MAP

#include <stdlib.h>
#include <stdio.h>
#include "mapBlock.h"
#include "coord.h"


class Map{
	public:	
		static const int MAPWIDTH = 100, MAPHEIGHT = 100;
		int height, width;

	private:
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
		void setBlockAt(MapBlock *mBlock, int x, int y);
		

};

#endif