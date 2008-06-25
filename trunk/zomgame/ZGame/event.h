/* An Event in the game, any variety of things like explosions, attacks, or effects */

#ifndef _EVENT_H
#define _EVENT_H

#include "entity.h"

class Event {
	public:
		enum EventType{ATTACK, MOVE};

	private:
		int tick;
		EventType eventType;

	public:
		Event();
		int getTick();
		int getType();
		void setTick(int nTick);
		void setType(EventType nEventType);
		
		virtual int resolve() = 0; //note: returns amount of time passed
};

#endif