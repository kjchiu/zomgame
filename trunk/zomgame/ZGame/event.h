/* An Event in the game, any variety of things like explosions, attacks, or effects */

#ifndef _EVENT_H
#define _EVENT_H

#include "entity.h"
#include "messagefactory.h"
#include "event_factory.h"

class EventFactory;

class Event {
	public:
		enum EventType{ATTACK, MOVE};

	private:
		int tick;
		EventType eventType;
		int thisID;
		static int id;

	public:
		Event();
		int getTick();
		int getType();
		void setTick(int nTick);
		void setType(EventType nEventType);
		
		virtual Message* resolve() = 0;
};

#endif