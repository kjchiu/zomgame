#include "event_add_effect.h"

EventAddEffect::EventAddEffect(Entity* _target, Effect* _effect) 
: target(_target), effect(_effect), Event(ADD_EFFECT) {
}

Message* EventAddEffect::resolve() {
	effect->setTickCount(getTick());
	target->addEffect(effect);
	char* buf = new char[128];
	sprintf_s(buf, 128, "target now has %d effects", target->getEffects()->size());
	
	return new Message(buf);
}