/* This represents an NPC, whether friendly or hostile (person or living, walking corpse) */

#ifndef _ENTITY_H
#define _ENTITY_H

#include "attribute.h"
#include "renderable.h"
#include "inventory.h"
#include "weapon.h"

using namespace std;

class Entity : public Renderable {

	protected:
		Coord* location;
		Inventory* inventory;
		vector<Attribute*>* attributes;
		Weapon* equippedWeapon;
		int speed;
		int siteRadius;
		enum EntityType{PLAYER, ZOMBIE};
		EntityType eType;

	public:
		Entity();
		Entity(bool isPlayer);
		Entity(bool isPlayer, string name);
		void init();
		virtual void addAttribute(Attribute* att);
		virtual void equip(Weapon* weapon);
		vector<Attribute*>* getAttributes();
		int getAttributeValue(string attName);
		Attribute* getAttribute(string attName);
		Weapon* getEquippedWeapon();
		virtual Inventory* getInventory();
		virtual Coord* getLoc();
		virtual int getValueOf(string attName); //returns the curValue only
		bool isPlayer();
		virtual void setLoc(Coord* nLocation);	
		virtual int getSpeed() { return speed; }
		virtual int getSiteRadius() { return siteRadius; }
		virtual void respawn(Coord* loc) { }
};

#endif