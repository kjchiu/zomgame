/* The referee class resolves any action that is accomplished between two objects */

#ifndef _REFEREE_H
#define _REFEREE_H

#include "all_includes.h"

class Referee {
	private:
		Game* game;
	public:
		Referee(Game*);
		int resolveEvents(int currentTick, EventDeque* eventDeque);
};

#endif
