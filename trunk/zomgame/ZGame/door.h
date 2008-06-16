/* A door that can open and close. */

#ifndef DOOR_H
#define DOOR_H

#include "prop.h"
#include "itemFactory.h"
class Door : public Prop {
	public:
		Door() {setName("Door"); setDisplayChar(0x2666); setPassable(false);}
		int interact(Player* p) {
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

		vector<Item*> destroy() {
			vector<Item*> debris;
			debris.push_back(ItemFactory::createWoodPlank());
			return debris;
		}
};

#endif DOOR_H