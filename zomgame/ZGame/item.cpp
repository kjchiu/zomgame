#include "item.h"

Item::Item(){
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