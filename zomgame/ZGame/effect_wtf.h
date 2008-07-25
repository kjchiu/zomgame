#ifndef _EFFECT_WTF_H_
#define _EFFECT_WTF_H_

#include "effect.h"
#include "game.h"

class EffectWtf : public Effect{
protected:
	Game* game;
public:
	EffectWtf(Game* game, int duration);
	int modify(Attributes type, int value);
};

#endif