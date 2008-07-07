/* This is a block on the map, filled with items, walls, nothing, etc */

#ifndef _MAPBLOCK_H
#define _MAPBLOCK_H

#include "all_includes.h"


using namespace std;


class MapBlock {
	private:
		Terrain* terrain;
		vector<Item*> itemList;
		vector<Entity*> entityList;
		vector<Prop*> propList;
		bool isTarget;
		
	public:
		MapBlock();
		void addEntity(Entity* entity);
		void addItem(Item* item);
		void addProp(Prop* prop);
		chtype getChar();
		short getColor();
		Item* getItemAt(int index);
		vector<Item*> getItems();
		Entity* getTopEntity();
		Prop* getTopProp();
		bool hasEntities();
		bool hasProps();
		bool isPassable();
		bool isObstacle();
		void removeEntity(Entity* entity);
		void removeItem(Item* item);
		void removeProp(Prop* prop);
		void setTerrain(Terrain* ter);
		Message* getBlockInfo();
		void loadFrom(ifstream &in);
		void saveTo(ofstream &out);

};

#endif