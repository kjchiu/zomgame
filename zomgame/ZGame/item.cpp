#include "item.h"

Item::Item(){
	setName("NewItem");
	setColor(5);
	setDescription("This is a generic item");
	setDisplayChar('$');
	setBulk(1);
	setWeight(1);
	setType("Generic");
}

int Item::getBulk(){
	return bulk;
}

string Item::getType(){
	return type;
}

int Item::getWeight(){
	return weight;
}

void Item::setBulk(int nBulk){
	bulk = nBulk;
}

void Item::setType(string nType){
	type = nType;
}

void Item::setWeight(int nWeight){
	weight = nWeight;
}