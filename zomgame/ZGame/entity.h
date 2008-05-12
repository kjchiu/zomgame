/* This represents an NPC, whether friendly or hostile (person or living, walking corpse) */

#ifndef _ENTITY_H
#define _ENTITY_H

#include "attribute.h"
#include "renderable.h"
#include "inventory.h"

using namespace std;

class Entity : public Renderable {
	protected:
		Coord* location;
		Inventory* inventory;
		vector<Attribute*>* attributes;
		
	public:
		Entity();
		Entity(string name);
		void init();
		virtual void addAttribute(Attribute* att);
		virtual vector<Attribute*>* getAttributes();
		virtual Inventory* getInventory();
		virtual Coord* getLoc();
		virtual int getValueOf(string attName);
		virtual void setLoc(Coord* nLocation);	
};

#endif