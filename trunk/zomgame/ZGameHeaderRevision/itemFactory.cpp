#include "itemFactory.h"

Item* ItemFactory::createItem(std::string name, Item::ItemType itemType){
	Item* item = new Item();
	item->setName(name);
	item->setType(itemType);
	return item;
}

Item* ItemFactory::createItem(std::string name, Item::ItemType itemType, string description){
	Item* item = new Item();
	item->setName(name);
	item->setType(itemType);
	item->setDescription(description);
	return item;
}

Weapon* ItemFactory::createWeapon(std::string name, Weapon::WeaponType wType, int damage){
	Weapon* weapon = new Weapon(name, damage);
	weapon->setWType(wType);
	return weapon;
}

Weapon* ItemFactory::createWeapon(std::string name, Weapon::WeaponType wType, int damage, string description){
	Weapon* weapon = new Weapon(name, damage);
	weapon->setWType(wType);
	weapon->setDescription(description);
	return weapon;
}

Item* ItemFactory::createWoodPlank() {
	Item* item = new Item();
	item->setName("Wood Plank");
	item->setType(Item::MATERIAL);
	item->setDescription("Piece of wood o.O?");
	item->setDisplayChar('%');
	return item;
}