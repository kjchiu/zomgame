/* A door that can open and close. */

#ifndef DOOR_H
#define DOOR_H

#include "prop.h"

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
};

#endif DOOR_H