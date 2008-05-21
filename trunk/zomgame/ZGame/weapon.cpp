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
	durability = new Attribute("Durability", 100);
}

int Weapon::getDamage(){
	return damage;
}

Attribute* Weapon::getDurability(){
	return durability;
}

string Weapon::getWClass(){
	return wClass;
}

void Weapon::setDamage(int nDmg){
	damage = nDmg;
}
void Weapon::setWClass(string nClass){
	wClass = nClass;
}
