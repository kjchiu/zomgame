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

string Item::getType(){
	switch (type) {
		case 0: return "NoType"; break;
		case 1: return "Food"; break;
		case 2: return "Weapon"; break;
		case 3: return "Container"; break;
	}
	return "NoType";
}

int Item::getWeight(){
	return weight;
}

void Item::removeSkill(int skillNum){
	int arraySize = associatedSkills->size();
	for (unsigned int i=0;i<arraySize;i++){
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
	//set up skills
	if (getType() == "Food") {
		int i;
	}
}

void Item::setWeight(int nWeight){
	weight = nWeight;
}

bool Item::operator==(const Item& otherItem) const {
	return (getID() == otherItem.getID());
}