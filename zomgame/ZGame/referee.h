/* The referee class resolves any action that is accomplished between two objects */

#ifndef _REFEREE_H
#define _REFEREE_H

#include "message.h"
#include "entity.h"
#include "item.h"
#include "globals.h"
#include <vector>
#include "messagefactory.h"
#include "game.h"

class Game;

class Referee {
	private:
		Game* game;
	public:
		Referee(Game*);
		bool doActionOnItem(Item* item, int skillIndex);
		bool pickUpItem(Entity* picker, Item* item, Message* msg);
		bool resolveAttack(Entity* attacker, Entity* defender, Message* msg);
		bool resolve(Player* player, void* target, int (*action)(Player*, void*, vector<Message*>*) );
};

#endif