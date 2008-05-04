#include "weapon.h"

Weapon::Weapon(){
	setName("Weapon");
	setDisplayChar('/');
	setDescription("This is some sort of weapon.");
	setType("Weapon");

	setWClass("Club");
	setCurDur(100);
	setMaxDur(100);
	setDamage(1);
}

int Weapon::getCurDur(){
	return curDurability;
}

int Weapon::getDamage(){
	return damage;
}

int Weapon::getMaxDur(){
	return maxDurability;
}

string Weapon::getWClass(){
	return wClass;
}

void Weapon::setCurDur(int nCurD){
	curDurability = nCurD;
}

void Weapon::setDamage(int nDmg){
	damage = nDmg;
}

void Weapon::setMaxDur(int nMaxD){
	maxDurability = nMaxD;
}

void Weapon::setWClass(string nClass){
	wClass = nClass;
}
