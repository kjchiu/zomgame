#include "inventory.h"

Inventory::Inventory(){
	totalWeight = 0;
	totalBulk = 0;
	items = vector<Item*>();
}

bool Inventory::addItem(Item* item){
	//check to see if possible first
	items.push_back(item);
	totalWeight += item->getWeight();
	totalBulk += item->getBulk();

	return true;
}

Item* Inventory::getItemAt(int index){
	return items.at(index);
}

int Inventory::getSize(){
	return items.size();
}

int Inventory::getTotalBulk(){
	return totalBulk;
}

int Inventory::getTotalWeight(){
	return totalWeight;
}

bool Inventory::removeItem(Item* item){
	for (unsigned int i=0; i<items.size(); i++){
		if (items.at(i)->getID() == item->getID()){
			if (i==0){
				items.pop_back();
			} else {
				items.erase(items.begin()+i-1, items.begin()+i); 
			}
		}
	}
	return true;
}