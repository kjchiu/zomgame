/* The referee class resolves any action that is accomplished between two objects */

#ifndef _REFEREE_H
#define _REFEREE_H

#include "message.h"
#include "entity.h"
#include "item.h"
#include "globals.h"

class Referee {
	private:

	public:
		Referee();
		bool pickUpItem(Entity* picker, Item* item, Message* msg);
		bool resolveAttack(Entity* attacker, Entity* defender, Message* msg);
};

#endif