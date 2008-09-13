#include "container_prop.h"
#include "game.h"

void ContainerProp::addItem(Item* item){
	items->push_back(item);
}

void ContainerProp::setItems(vector<Item*>* nItems){
	items = nItems;
}

int ContainerProp::interact(Player* p) {
	//open up the container
	bool highlightLeft = false; //put the inventory highlight on the right side
	if (items->empty()){
		highlightLeft = true;
	}
	Game::getInstance()->openInventory(items, highlightLeft);
	return 5;
}

vector<Item*> ContainerProp::destroy() {
	vector<Item*> debris;
	debris.push_back(ItemFactory::createWoodPlank());
	//for each item in the box, have it randomly break
	return debris;
}