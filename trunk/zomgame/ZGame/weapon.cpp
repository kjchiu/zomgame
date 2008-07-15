#include "weapon.h"
#include "globals.h"

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
	setWType(Weapon::MELEE);
	durability = new Attribute("Durability", 100);
	this->addSkill(skill_list.getSkillID("Equip"));
	this->addSkill(skill_list.getSkillID("Repair"));
}

int Weapon::getDamage(){
	return damage;
}

Attribute* Weapon::getDurability(){
	return durability;
}

int Weapon::getWType(){
	return wType;
}

string Weapon::getWTypeString(){
	//return "Weapon"; //will return a string represenation of the weapon's class
	return isMelee() ? "Melee" : "Ranged";
}

int Weapon::getRange() {
	return range;
}

bool Weapon::isMelee(){
	if (wType == Weapon::MELEE){
		return true;
	}
	return false;
}

void Weapon::setDamage(int nDmg){
	damage = nDmg;
}
void Weapon::setWType(WeaponType nType){
	wType = nType;
}

void Weapon::setRange(int _range) {
	range = _range;
}
