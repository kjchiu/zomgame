/* This is a block on the map, filled with items, walls, nothing, etc */

#ifndef MAPBLOCK
#define MAPBLOCK

#include <cstdlib>
#include <vector>

#include "entity.h"
#include "terrain.h"
#include "terrains\terrains_list.h"

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
		Terrain* terrain;
		vector<int> itemList;
		vector<Entity*> entityList;
		//itemarray

	public:
		MapBlock();
		void addEntity(Entity* entity);
		char getChar();
		short getColor();
		bool isPassable();
		void removeEntity(Entity* entity = NULL);
		char returnchar;
		void setTerrain(Terrain* ter);
};

#endif