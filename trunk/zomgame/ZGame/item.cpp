#include "item.h"

Item::Item(){
	setName("NewItem");
	setColor(1);
	setDescription("This is a generic item");
	setDisplayChar('/');
}

int Item::getBulk(){
	return bulk;
}

int Item::getWeight(){
	return weight;
}

void Item::setBulk(int nBulk){
	bulk = nBulk;
}

void Item::setWeight(int nWeight){
	weight = nWeight;
}