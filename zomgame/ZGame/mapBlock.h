/* This is a block on the map, filled with items, walls, nothing, etc */

#ifndef MAPBLOCK
#define MAPBLOCK

#include <cstdlib>
#include <vector>

#include "entity.h"

using namespace std;

struct mapData {
	union data {
			//Object o,
			//Prop p,
			//Entity e,
	};
	int height;
};

class MapBlock {
	private:
		char terrain;
		vector<int> itemList;
		vector<Entity*> entityList;
		//itemarray

	public:
		MapBlock();
		void addEntity(Entity* entity);
		char getChar();
		bool isPassable();
		void removeEntity(Entity* entity);
		char returnchar;
		void setTerrain(char ter);
};

#endif