#include "player.h"


Player::Player(){
	name = "NameHere";
	location = new Coord();
	displayChar = '@';
}

Coord* Player::getLoc(){
	return location;
}

void Player::setLoc(Coord* nLocation){
	*location = *nLocation;
}

vector<Skill*>* Player::getSkills() {
	vector<Skill*>* skill_list = new vector<Skill*>();
	for (int i = 0; i < skills.size(); i ++) {
		
	}
	return NULL;
}
