/* Produces items */

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "item.h"
#include "weapon.h"

class ItemFactory {

	public:
		static Item* createItem(string name, Item::ItemType itemType);
		static Item* createItem(string name, Item::ItemType itemType, string description);
		static Weapon* createWeapon(string name, Weapon::WeaponType wType, int damage);
		static Weapon* createWeapon(string name, Weapon::WeaponType wType, int damage, string description);

};

#endif
