/* This is a block on the map, filled with items, walls, nothing, etc */

#ifndef MAPBLOCK
#define MAPBLOCK

#include <cstdlib>
#include <vector>



class MapBlock {
	private:
		char terrain;
		vector<int, int> itemList;
		//itemarray

	public:
		MapBlock();
		char getChar();
		char returnchar;
		void setTerrain(char ter);

};

#endif