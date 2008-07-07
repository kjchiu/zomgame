/* This represents an NPC, whether friendly or hostile (person or living, walking corpse) */

#ifndef _ENTITY_H
#define _ENTITY_H

#include "all_includes.h"

using namespace std;


class Entity : public Renderable, public Attackable {
public:
	enum EntityType{PLAYER, ZOMBIE};
	protected:
		Coord* location;
		Inventory* inventory;
		vector<Attribute*>* attributes;
		Weapon* equippedWeapon;
		int speed;
		int siteRadius;
		
		EntityType eType;

	public:

		Entity();
		Entity(string name);
		void init();
		virtual void addAttribute(Attribute* att);
		virtual void equip(Weapon* weapon);
		vector<Attribute*>* getAttributes();
		int getAttributeValue(string attName);
		Attribute* getAttribute(string attName);
		Weapon* getEquippedWeapon();
		int getType();
		void setType(EntityType nType);
		virtual Inventory* getInventory();
		virtual Coord* getLoc();
		virtual int getValueOf(string attName); //returns the curValue only
		bool isPlayer();
		virtual void setLoc(Coord* nLocation);	
		virtual int getSpeed() { return speed; }
		virtual int getSiteRadius() { return siteRadius; }
		virtual void respawn(Coord* loc) { }

		virtual Attribute* getHealth();
		virtual vector<Item*> destroy();
};

#endif