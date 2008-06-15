#include "weaponFactory.h"

Weapon* WeaponFactory::createPistol() {
	Weapon* pistol = new Weapon("Pistol", 20);
	pistol->setRange(20);
	pistol->setWType(Weapon::RANGED);
	pistol->setDisplayChar(0xAC);
	return pistol;
}

Weapon* WeaponFactory::createFists() {
	Weapon* fists = new Weapon("fists", 10);
	fists->setRange(0);
	fists->setWType(Weapon::MELEE);
	return fists;
}