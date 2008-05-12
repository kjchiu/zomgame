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

void Entity::addAttribute(Attribute* att){
	for (int i=0; i<attributes->size(); i++){
		if (attributes->at(i)->getName() == att->getName()){
			return; //the attribute already is in the list
		}
	}
	//if the attribute is not in the list
	attributes->push_back(att);
}

vector<Attribute*>* Entity::getAttributes(){
	return attributes;
}

Inventory* Entity::getInventory(){
	return inventory;
}

Coord* Entity::getLoc(){
	return location;
}

int Entity::getValueOf(string attName){
	for (int i=0; i<attributes->size(); i++){
		if (attributes->at(i)->getName() == attName){
			return attributes->at(i)->getValue();
		}
	}
}

void Entity::setLoc(Coord* newLoc){
	location = newLoc;
}
