/* A door that can open and close. */

#ifndef DOOR_H
#define DOOR_H

#include "prop.h"
#include "itemFactory.h"
class Door : public Prop {
	public:
		Door() {setName("Door"); setDisplayChar(0x2666); setPassable(false);}
		int interact(Player* p);
		vector<Item*> destroy();
};

#endif DOOR_H