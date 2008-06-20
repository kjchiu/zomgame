#include "player.h"


Player::Player() : Entity(){
	name = "NameHere";
	location = new Coord();
	displayChar = '@';
	int i = 0;
	skills = new vector<SkillValue>();
	SkillValue sValue;
	while (Skill* skill = skill_list.getSkill(i)){
		sValue.skill = i;
		sValue.level = 0;
		sValue.tagged = false;
		skills->push_back(sValue);
		i++;
	}
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

vector<SkillValue>* Player::getSkills() {
	return skills;
}

int Player::getSkillValue(int skill){
	for (unsigned int i = 0; i<skills->size(); i++){
		if (skills->at(i).skill == skill){
			return skills->at(i).level;
		}
	}
	return -1;
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
