/* Produces events */

#ifndef _EVENT_FAC_H
#define _EVENT_FAC_H

#include "event_types.h"

class Event;

class EventFactory {
	private:
	public:
		static AttackEvent* createAttackEvent(Entity* nAttacker, Entity* nDefender, int tick);
};

#endif