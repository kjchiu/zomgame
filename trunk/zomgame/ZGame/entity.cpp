#include "entity.h"

int Entity::id = 0;

Entity::Entity(){
	thisID = id++;	
	color = 2;
}

Entity::Entity(string newName){
	setName(newName);
	thisID = id++;	
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
