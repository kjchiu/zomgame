#include "player.h"


Player::Player(){
	name = "NameHere";
	location = new Coord();
	displayChar = '@';
	skills.push_back(0);
	skills.push_back(1);
	skills.push_back(2);
	skills.push_back(3);
	equip(NULL);
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
