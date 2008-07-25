#ifndef _EVENT_ADD_EFFECT_H_
#define _EVENT_ADD_EFFECT_H_

#include "event.h"

class EventAddEffect : public Event {
protected:
	Entity* target;
	Effect* effect;
public:
	EventAddEffect(Entity* _target, Effect* _effect);
	Message* resolve();
};

#endif