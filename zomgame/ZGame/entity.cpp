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
	inventory = new Inventory();
}

Inventory* Entity::getInventory(){
	return inventory;
}

Coord* Entity::getLoc(){
	return location;
}

void Entity::setLoc(Coord* newLoc){
	location = newLoc;
}
