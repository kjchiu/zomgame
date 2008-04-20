/* This is a map, basically a wrapper class for the world, an array of CHAR_INFOs */
#ifndef MAP
#define MAP

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "mapBlock.h"


class Map{
	public:	
		static const int MAPWIDTH = 80, MAPHEIGHT = 50;
		static const int VIEWWIDTH = 50, VIEWHEIGHT = 30;

	private:
		MapBlock* map[MAPWIDTH*MAPHEIGHT];	//this is essentially the entire 'world'
		CHAR_INFO viewMap[MAPWIDTH*MAPHEIGHT]; //this is what the player can see

	public:
		Map();
		void clear();
		void drawMenu();
		void draw();
		char getCharAt(int x, int y);
		MapBlock* getMap();
		CHAR_INFO* getViewableMap(int pX, int pY);
		void setCharAt(char setChar, int x, int y);
		

};

#endif