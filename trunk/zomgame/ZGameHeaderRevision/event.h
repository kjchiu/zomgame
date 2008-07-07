/* An Event in the game, any variety of things like explosions, attacks, or effects */

#ifndef _EVENT_H
#define _EVENT_H

#include "all_includes.h"

class Event {
	public:
		enum EventType{ATTACK, RANGED_ATTACK, GET_ITEM, DROP_ITEM, MOVE, SPAWN_ENT, SPAWN_ITEM, SPAWN_PROP, INTERACT, SKILL};

	private:
		friend class Referee;
		int tick;
		EventType eventType;
		int thisID;
		static int id;
	public:
		Event(EventType _type);
		int getTick();
		int getType();
		void setTick(int nTick);
		void setType(EventType nEventType);

		static void initGamePtr(Game* nGame);
		virtual Message* resolve() = 0;
};

#endif