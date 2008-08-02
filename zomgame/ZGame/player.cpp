#include "player.h"


Player::Player() : Entity(){
	speed = 10;
	setType(Entity::PLAYER);
	name = "NameHere";
	location = new Coord();
	displayChar = '@';
	//addAttribute(new Attribute("Hunger", 1000));
	//addAttribute(new Attribute("Thirst", 1000));
	//addAttribute(new Attribute("Stamina", 1000));
	addAttribute(AttributeFactory::getHealth(1000));
	addAttribute(AttributeFactory::getStamina());
	addAttribute(AttributeFactory::getStrength());
	addAttribute(AttributeFactory::getHunger());
	addAttribute(AttributeFactory::getThirst());
	skills = new vector<SkillValue>();
	SkillValue sValue;
	int i = 0;
	while (Skill* skill = skill_list.getSkill(i)){
		sValue.skill = i;
		sValue.level = 1;
		sValue.experience = 0;
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

SkillValue* Player::getSkill(int skill){
	for (unsigned int i = 0; i<skills->size(); i++){
		if (skills->at(i).skill == skill){
			return &(skills->at(i));
		}
	}
	return NULL;
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


