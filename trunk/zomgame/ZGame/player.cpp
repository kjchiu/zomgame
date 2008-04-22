#include "player.h"

Player::Player(){
	name = "NameHere";
	location = new Coord();
}

Coord* Player::getLoc(){
	return location;
}

char* Player::getName() {
	return name;
}

void Player::setLoc(Coord* nLocation){
	*location = *nLocation;
}

void Player::setName(char *nName){
	name = nName;
}

void Player::draw(Map *map){
	map->setCharAt('@', location->getX(), location->getY());
}

