#include "entity.h"

Entity::Entity(){
	init();
}

Entity::Entity(string newName){
	setName(newName);
	init();
}

void Entity::init(){
	color = 2;
}

Coord* Entity::getLoc(){
	return location;
}

void Entity::setLoc(Coord* newLoc){
	location = newLoc;
}
