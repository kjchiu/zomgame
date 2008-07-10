/* Produces items */

#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include "weapon.h"
#include "medical_item.h"
#include "globals.h"

class ItemFactory {

	public:
		static Item* createItem(string name, Item::ItemType itemType);
		static Item* createItem(string name, Item::ItemType itemType, string description);
		static Weapon* createWeapon(string name, Weapon::WeaponType wType, int damage);
		static Weapon* createWeapon(string name, Weapon::WeaponType wType, int damage, string description);
		static Item* createWoodPlank();
		static MedicalItem* createMedicalItem(string nName, int nHealPot); 

};

#endif
