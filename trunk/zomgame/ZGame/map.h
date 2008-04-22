/* This is a map, basically a wrapper class for the world, an array of CHAR_INFOs */
#ifndef MAP
#define MAP

#include <stdlib.h>
#include <stdio.h>
#include "mapBlock.h"


class Map{
	public:	
		static const int MAPWIDTH = 100, MAPHEIGHT = 100;

	private:
		MapBlock* map[MAPWIDTH*MAPHEIGHT];	//this is essentially the entire 'world'
		
	public:
		Map();
		void clear();
		void draw();
		MapBlock* getBlockAt(int x, int y);
		char getCharAt(int x, int y);
		MapBlock* getMap();
		//CHAR_INFO* getViewableMap(int pX, int pY);
		void setCharAt(char setChar, int x, int y);
		void setBlockAt(MapBlock *mBlock, int x, int y);
		

};

#endif