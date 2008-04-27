/* This is a block on the map, filled with items, walls, nothing, etc */

#ifndef MAPBLOCK
#define MAPBLOCK

#include <vector>

#include "entity.h"
#include "terrain.h"
#include "prop.h"
#include "TerrainTypes\terrain_types.h"
#include "curses.h"

using namespace std;

struct mapData {
	union data {
			//Object o,
			//Prop p,
			//Entity* e;
	};
	int height;
};

class MapBlock {
	private:
		Terrain* terrain;
		vector<int> itemList;
		vector<Entity*> entityList;
		vector<Prop*> propList;
		
	public:
		MapBlock();
		void addEntity(Entity* entity);
		void addProp(Prop* prop);
		chtype getChar();
		short getColor();
		Entity* getTopEntity();
		bool hasEntities();
		bool isPassable();
		void removeEntity(Entity* entity);
		void removeProp(Prop* prop);
		void setTerrain(Terrain* ter);
};

#endif