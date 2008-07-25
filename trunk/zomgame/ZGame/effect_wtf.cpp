#include "effect_wtf.h"

EffectWtf::EffectWtf(Game* _game, int _duration) 
:	game(_game) , Effect() {
	duration = _duration;
}

int EffectWtf::modify(Attributes type, int value) {
	char* buf = new char[96];
	sprintf_s(buf, 96, "WTFEFFECT - started: %d time left %d", start_tick, duration);
	game->addMessage(new Message(buf));
	return value;
}

