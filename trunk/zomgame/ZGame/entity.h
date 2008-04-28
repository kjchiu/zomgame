/* This represents an NPC, whether friendly or hostile (person or living, walking corpse) */

#ifndef _ENTITY_H
#define _ENTITY_H

#include "renderable.h"
#include "inventory.h"

using namespace std;

class Entity : public Renderable {
	protected:
		Coord* location;
		Inventory* inventory;
		
	public:
		Entity();
		Entity(string name);
		void init();
		virtual Inventory* getInventory();
		virtual Coord* getLoc();
		virtual void setLoc(Coord* nLocation);
		
};

#endif