/* This represents an NPC, whether friendly or hostile (person or living, walking corpse) */

#ifndef _ENTITY_H
#define _ENTITY_H

#include "attackable.h"
#include "attribute.h"
#include "attribute_factory.h"
#include "renderable.h"
#include "inventory.h"
#include "weapon.h"
#include "effect.h"

using namespace std;



class Entity : public Renderable, public Attackable {
public:
	enum EntityType{PLAYER, ZOMBIE};
	
	protected:
		Coord* location;
		Inventory* inventory;
		vector<Attribute*>* attributes;
		vector<Effect*>* effects;
		Weapon* equippedWeapon;
		int speed;
		int siteRadius;
		
		EntityType eType;

	public:

		Entity();
		Entity(string name);
		void init();
		void addEffect(Effect* effect);
		vector<Effect*>* getEffects();

		

		virtual void addAttribute(Attribute* att);
		Attribute* getAttribute(Attributes type);
		vector<Attribute*>* getAttributes();
		int getAttributeValue(string attName);
		int getAttributeValue(Attributes type);
		Attribute* getAttribute(string attName);

		virtual void equip(Weapon* weapon);
		Weapon* getEquippedWeapon();

		int getType();
		void setType(EntityType nType);

		virtual Inventory* getInventory();
		virtual vector<string*>* getInventoryStrings();
		virtual Coord* getLoc();
		virtual int getValueOf(string attName); //returns the curValue only
		bool isPlayer();
		virtual void setLoc(Coord* nLocation);	
		virtual int getSpeed() { return speed; }
		virtual int getSiteRadius() { return siteRadius; }
		virtual void respawn(Coord* loc) { }

		
		
		virtual Attribute* getHealth();
		void tickEffects(int tick);
		virtual vector<Item*> destroy();
};

#endif