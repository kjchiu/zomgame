/* A weapon in the game. Inherits from Item, and has some properties in addition to it. */

#ifndef _WEAPON_H
#define _WEAPON_H

#include "all_includes.h"


using namespace std;

class Weapon : public Item {
	
	public:
		enum WeaponType {MELEE, RANGED};

	private:
		WeaponType wType; //relates to what skill is associated with the weapon
		int damage;
		Attribute* durability; //likely always going to have 100, maybe this can be modified?
		int range;
	public:
		Weapon();
		Weapon(string nName, int damage);
		void init(string nName, int damage);
		bool isMelee();
		Attribute* getDurability();
		int getWType();
		string getWTypeString();
		int getDamage();
		int getRange();
		void setWType(WeaponType nType);
		void setDamage(int nDamage);
		void setRange(int _range);
	
};

#endif