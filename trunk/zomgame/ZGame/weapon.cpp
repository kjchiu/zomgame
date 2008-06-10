#include "weapon.h"

Weapon::Weapon(){
	setDescription("Your bare hands. Not very damaging.");
	init("Bare Hands", 1);
}

Weapon::Weapon(string nName, int damage){
	init(nName, damage);
}

void Weapon::init(string nName, int damage){
	setName(nName);
	setDamage(damage);
	setDisplayChar('/');
	setType(Item::WEAPON);
	setWClass(Weapon::MELEE);
	durability = new Attribute("Durability", 100);
}

int Weapon::getDamage(){
	return damage;
}

Attribute* Weapon::getDurability(){
	return durability;
}

string Weapon::getWClass(){
	return "Weapon"; //will return a string represenation of the weapon's class
}

bool Weapon::isMelee(){
	if (wClass == Weapon::MELEE){
		return true;
	}
	return false;
}

void Weapon::setDamage(int nDmg){
	damage = nDmg;
}
void Weapon::setWClass(WeaponClass nClass){
	wClass = nClass;
}
