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
		int curHealth, maxHealth;
		
	public:
		Entity();
		Entity(string name);
		void init();
		virtual void addAttribute(Attribute* att);
		virtual vector<Attribute*>* getAttributes();
		virtual int getCurHealth();
		virtual Inventory* getInventory();
		virtual int getMaxHealth();
		virtual Coord* getLoc();
		virtual int getValueOf(string attName);
		virtual void setCurHealth(int nCurHealth);
		virtual void setLoc(Coord* nLocation);	
		virtual void setMaxHealth(int nMaxHealth);
	
};

#endif