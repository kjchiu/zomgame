#include "entity.h"

int Entity::id = 0;

Entity::Entity(){
	thisID = id++;	
	color = 2;
}

Entity::Entity(string name){
	setName(name);
}

string Entity::getDescription(){
	return desc;
}

char Entity::getDisplayChar(){
	return displayChar;
}

short Entity::getColor() {
	return color;
}

int Entity::getID(){
	return thisID;
}

Coord* Entity::getLoc(){
	return location;
}

string Entity::getName(){
	return name;
}

void Entity::setDescription(string newDesc){
	desc = newDesc;
}

void Entity::setDisplayChar(char newDispChar){
	displayChar = newDispChar;
}

void Entity::setColor(short newColor) {
	color = newColor;
}

void Entity::setLoc(Coord *nLoc){
	location = nLoc;
}

void Entity::setName(string newName){
	name = newName;
}