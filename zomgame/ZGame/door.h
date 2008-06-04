/* A door that can open and close. */

#ifndef DOOR_H
#define DOOR_H

#include "prop.h"

class Door : public Prop {
	public:
		Door() {setName("Door"); setDisplayChar(174); setPassable(false);}
		void interact(Player* p) {
			if (isPassable()){
				setDisplayChar(174);
				setPassable(false);
			} else {
				setDisplayChar(' ');
				setPassable(true);
			}
		}
};

#endif DOOR_H