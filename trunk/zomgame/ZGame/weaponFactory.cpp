#include "weaponFactory.h"

Weapon* WeaponFactory::createPistol() {
	Weapon* pistol = new Weapon("Pistol", 20);
	pistol->setRange(20);
	pistol->setWType(Weapon::HANDGUN);
	pistol->setDisplayChar(0xAC);
	pistol->getDurability()->init(pistol->getDurability()->getName(), 1000,1000);
	return pistol;
}

Weapon* WeaponFactory::createFists() {
	Weapon* fists = new Weapon("fists", 1);
	fists->setRange(0);
	fists->setWType(Weapon::UNARMED);
	return fists;
}