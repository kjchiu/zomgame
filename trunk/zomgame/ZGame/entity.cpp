#include "entity.h"

int Entity::id = 0;

Entity::Entity(){
	string name = "Entity #";
	name += id+1;
	setName(name);
	init();
}

Entity::Entity(string newName){
	setName(newName);
	init();
}

void Entity::init(){
	thisID = ++id;
	color = 2;
}

int Entity::getID(){
	return thisID;
}

Coord* Entity::getLoc(){
	return location;
}

void Entity::setLoc(Coord* newLoc){
	location = newLoc;
}
