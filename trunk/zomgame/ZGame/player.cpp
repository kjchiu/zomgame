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





