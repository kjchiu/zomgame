/* The referee class resolves any action that is accomplished between two objects */

#ifndef _REFEREE_H
#define _REFEREE_H

#include "direction.h"
#include "game.h"
#include "message.h"
#include "entity.h"
#include "item.h"
#include "globals.h"
#include <vector>
#include "messagefactory.h"
#include "event_factory.h"
#include "event_dq.h"

class Game;

class Referee {
	private:
		Game* game;
	public:
		Referee(Game*);
		int attackLocation(Entity* attacker, Coord* loc, Message* msg);
		int attackRngLocation(Player* player, Coord* loc, Message* msg);
		int attackDirection(Entity* attacker, Direction dir);
		bool doActionOnItem(Item* item, int skillIndex);
		int interact(Player* player, Prop* prop);
		bool dropItem(Entity* dropper, int index, Message* msg);
		bool pickUpItem(Entity* picker, MapBlock* loc, int index, Message* msg);
		bool resolveAttack(Entity* attacker, Entity* defender, Message* msg);
		bool resolve(Player* player, void* target, int (*action)(Player*, void*, vector<Message*>*) );
		int resolveEvents(int currentTick, EventDeque* eventDeque);
		int destroy(Prop* prop, Coord* loc);
		int destroy(Entity* ent, Coord* loc);
};

#endif
