/* An Event in the game, any variety of things like explosions, attacks, or effects */

#ifndef _EVENT_H
#define _EVENT_H

class Event {
	private:
		int tick;

	public:
		Event();
		int getTick();
		void setTick(int nTick);
};

#endif