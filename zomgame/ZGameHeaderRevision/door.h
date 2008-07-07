/* A door that can open and close. */

#ifndef _DOOR_H
#define _DOOR_H

#include "all_includes.h"

class Door : public Prop {
	public:
		Door() {setName("Door"); setDisplayChar(0x2666); setPassable(false);}
		int interact(Player* p);
		vector<Item*> destroy();
};

#endif