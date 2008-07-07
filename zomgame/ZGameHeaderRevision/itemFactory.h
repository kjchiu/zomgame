/* Produces items */

#ifndef _ITEMFACTORY_H
#define _ITEMFACTORY_H

#include "all_includes.h"

class ItemFactory {

	public:
		static Item* createItem(string name, Item::ItemType itemType);
		static Item* createItem(string name, Item::ItemType itemType, string description);
		static Weapon* createWeapon(string name, Weapon::WeaponType wType, int damage);
		static Weapon* createWeapon(string name, Weapon::WeaponType wType, int damage, string description);
		static Item* createWoodPlank();

};

#endif
