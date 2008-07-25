#include "effect.h"

int Effect::count = 0;

Effect::Effect() {
}

void Effect::setTickCount(int tick) {
	last_tick = tick;
	start_tick = tick;
}

bool Effect::tick(int tick) {
	duration -= tick - last_tick;
	if (duration <= 0) {
		return false;
	} else {
		last_tick = tick;
	}
}