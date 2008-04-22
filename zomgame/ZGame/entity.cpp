#include "entity.h"

int Entity::id = 0;

Entity::Entity(){
	thisID = id++;	
}

string Entity::getDescription(){
	return desc;
}

char Entity::getDisplayChar(){
	return displayChar;
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

void Entity::setName(string newName){
	name = newName;
}