#include "all_includes.h"

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
	attributes = new vector<Attribute*>();
	addAttribute(new Attribute("Health", 1000));
	equip(NULL);
}

void Entity::addAttribute(Attribute* att){
	for (unsigned int i = 0; i < attributes->size(); i++){
		if (attributes->at(i)->getName() == att->getName()){
			if (i==attributes->size()-1){
				attributes->pop_back();
			} else {
				attributes->erase(attributes->begin()+i, attributes->begin()+i+1); 
			} 
		}
	}
	//if the attribute is not in the list
	attributes->push_back(att);
}

void Entity::equip(Weapon* weapon){
	equippedWeapon = weapon;
}

vector<Attribute*>* Entity::getAttributes(){
	return attributes;
}

int Entity::getAttributeValue(string attName){
	for (unsigned int i=0; i<attributes->size(); i++){
		if (attributes->at(i)->getName() == attName){
			return attributes->at(i)->getCurValue();
		}
	}
	return -1;
}

Attribute* Entity::getAttribute(string attName){
	for (unsigned int i=0; i<attributes->size(); i++){
		if (attributes->at(i)->getName() == attName){
			return attributes->at(i);
		}
	}
	return new Attribute();
}

Attribute* Entity::getHealth() {
	return getAttribute("Health");
}
Weapon* Entity::getEquippedWeapon(){
	if (equippedWeapon == NULL){
		return new Weapon(); //returns bare fists
	}
	return equippedWeapon;
}

Inventory* Entity::getInventory(){
	return inventory;
}

Coord* Entity::getLoc(){
	return location;
}

int Entity::getType(){
	return eType;
}

int Entity::getValueOf(string attName){
	for (unsigned int i = 0; i < attributes->size(); i++){
		if (attributes->at(i)->getName() == attName){
			return attributes->at(i)->getCurValue();
		}
	}
	return -1;
}

bool Entity::isPlayer(){
	if (getType() == Entity::PLAYER){
		return true;
	}
	return false;
}

void Entity::setLoc(Coord* newLoc){
	location = newLoc;
}

void Entity::setType(EntityType nType){
	eType = nType;
}

std::vector<Item*> Entity::destroy() {
	return std::vector<Item*>();
}