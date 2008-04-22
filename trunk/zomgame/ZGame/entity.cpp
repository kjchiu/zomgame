#include "entity.h"

int Entity::id = 0;

Entity::Entity(){
	thisID = id++;	
	color = 2;
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

void Entity::setName(string newName){
	name = newName;
}