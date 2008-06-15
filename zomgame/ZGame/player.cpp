#include "player.h"


Player::Player() : Entity(){
	name = "NameHere";
	location = new Coord();
	displayChar = '@';
	skills.push_back(0);
	skills.push_back(1);
	skills.push_back(2);
	skills.push_back(3);

	eqRngWeapon = NULL;
}
void Player::equip(Weapon* weapon){
	if (weapon->isMelee()){
		equippedWeapon = weapon;
		return;
	} else {
		eqRngWeapon = weapon;
	}
}

Weapon* Player::getEqRngWeapon(){
	return eqRngWeapon;
}

Coord* Player::getLoc(){
	return location;
}

void Player::setLoc(Coord* nLocation){
	*location = *nLocation;
}

vector<int>* Player::getSkills() {
	vector<int>* skill_list = new vector<int>();
	for (int i = 0; i < skills.size(); i ++) {
		skill_list->push_back(skills.at(i));
	}
	return skill_list;
}

void Player::unequip(Weapon* weapon){
	if (weapon->isMelee()){
		equippedWeapon = NULL;
		return;
	} 
	eqRngWeapon = NULL;
}

void Player::respawn(Coord *loc) {
	
}
