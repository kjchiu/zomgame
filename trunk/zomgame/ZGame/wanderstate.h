#ifndef _WANDERSTATE_H_
#define _WANDERSTATE_H_
#include "zombie.h"
class WanderState : public BrainState {
private:
	WanderState() : BrainState(NULL) {};
protected:
	int wanderChance;
	Game::Direction dir;
public:
	WanderState(Zombie*);
	virtual ~WanderState() {}
	virtual void tick(Game* game);
};
#endif