#include "item.h"

int Item::id = 0;

Item::Item(){
	thisID = ++id;
	setName("NewItem");
	setColor(5);
	setDescription("This is a generic item");
	setDisplayChar('$');
	setBulk(1);
	setWeight(1);
	setType(Item::NOTYPE);
	associatedSkills = new vector<int>();
}

void Item::addSkill(int skillNum){
	associatedSkills->push_back(skillNum);
}

int Item::getBulk(){
	return bulk;
}

int Item::getID() const {
	return thisID;	
}

vector<int>* Item::getSkills(){
	return associatedSkills;
}

int Item::getType(){
	return type;
}

string Item::getTypeString(){
	ItemType thisType = type;
	if (type == Item::AMMO){
		return "Ammo";
	} else if (type == Item::CONTAINER){
		return "Container";
	} else if (type == Item::FOOD){
		return "Food";
	} else if (type == Item::MATERIAL){
		return "Material";
	} else if (type == Item::WEAPON){
		return "Weapon";
	} 
	return "NoType";
}

int Item::getWeight(){
	return weight;
}

void Item::removeSkill(int skillNum){
	unsigned int arraySize = associatedSkills->size();
	for (unsigned int i = 0; i < arraySize; i++){
		if (associatedSkills->at(i) == skillNum){
			if (i==arraySize - 1){
				associatedSkills->pop_back();
				return;
			} else {
				associatedSkills->erase(associatedSkills->begin()+i, associatedSkills->begin()+i+1); 
				return;
			} 
		}
	}
}

void Item::setBulk(int nBulk){
	bulk = nBulk;
}

void Item::setType(ItemType nType){
	type = nType;
}

void Item::setWeight(int nWeight){
	weight = nWeight;
}

bool Item::operator==(const Item& otherItem) const {
	if (&otherItem == NULL){
		return false;
	}
	return (getID() == otherItem.getID());
}