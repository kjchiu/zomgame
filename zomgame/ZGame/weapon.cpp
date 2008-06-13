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
}

int Weapon::getDamage(){
	return damage;
}

Attribute* Weapon::getDurability(){
	return durability;
}

//WeaponType Weapon::getWType(){
//	return wType;
//}

string Weapon::getWTypeString(){
	return "Weapon"; //will return a string represenation of the weapon's class
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
