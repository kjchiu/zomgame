#include "entity.h"
#include "weaponfactory.h"

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
	effects = new vector<Effect*>();
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

vector<Effect*>* Entity::getEffects() {
	return effects;
}

vector<Attribute*>* Entity::getAttributes(){
	return attributes;
}

int Entity::getAttributeValue(string attName){
	Attribute* attribute = getAttribute(attName);
	int value = attribute->getCurValue();
	for (int i = 0; i < effects->size(); i++) {
		value = effects->at(i)->modify(attribute->getType(), value);
	}
	return value;
}

int Entity::getAttributeValue(Attributes type) {
	Attribute* attribute = getAttribute(type);
	if (attribute) {
		int value = attribute->getCurValue();
		for (int i = 0; i < effects->size(); i++) {
			value = effects->at(i)->modify(attribute->getType(), value);
		}
		return value;
	} else {
		return 0;
	}
}

Attribute* Entity::getAttribute(string attName){
	for (unsigned int i=0; i<attributes->size(); i++){
		if (attributes->at(i)->getName() == attName){
			return attributes->at(i);
		}
	}
	return new Attribute();
}

Attribute* Entity::getAttribute(Attributes type) {
	for (unsigned int i = 0; i < attributes->size(); i++) {
		if (attributes->at(i)->getType() == type) {
			return attributes->at(i);
		}
	}
	return NULL;
}

Attribute* Entity::getHealth() {
	return getAttribute("Health");
}
Weapon* Entity::getEquippedWeapon(){
	if (equippedWeapon == NULL){
		return WeaponFactory::createFists(); //returns bare fists
	}
	return equippedWeapon;
}

Inventory* Entity::getInventory(){
	return inventory;
}

vector<string*>* Entity::getInventoryStrings(){
	vector<string*>* strings = new vector<string*>();
	for (int i=0; i < inventory->getSize(); i++){
		string* name = new string(inventory->getItemAt(i)->getName());
		strings->push_back(name);
	}

	return strings;
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

void Entity::addEffect(Effect *effect) {
	effects->push_back(effect);
}

void Entity::tickEffects(int tick) {
	for (unsigned int i = 0; i < effects->size(); i++)  {
		effects->at(i)->tick(tick);
	}
}

