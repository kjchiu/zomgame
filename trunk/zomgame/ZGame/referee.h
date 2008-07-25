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
		int resolveEvents(int currentTick, EventDeque* eventDeque);
		int resolveEffects(vector<Effect*>* effects);
};

#endif
