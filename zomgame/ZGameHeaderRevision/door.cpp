#include "door.h"

int Door::interact(Player* p) {
	if (isPassable()){
		setDisplayChar(0x2666);
		setPassable(false);
		return 5;
	} else {
		setDisplayChar(' ');
		setPassable(true);
		return 0;
	}
}

vector<Item*> Door::destroy() {
	vector<Item*> debris;
	debris.push_back(ItemFactory::createWoodPlank());
	return debris;
}