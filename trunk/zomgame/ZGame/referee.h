/* The referee class resolves any action that is accomplished between two objects */

#ifndef _REFEREE_H
#define _REFEREE_H

#include "message.h"
#include "entity.h"

class Referee {
	private:

	public:
		Referee();
		Message* resolveAttack(Entity* attacker, Entity* defender);
};

#endif