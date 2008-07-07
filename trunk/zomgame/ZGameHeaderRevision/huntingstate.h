#ifndef _HUNTINGSTATE_H_
#define _HUNTINGSTATE_H_
#include "zombie.h"
class HuntingState : public BrainState {
private:
	HuntingState() : BrainState(NULL) {};
protected:
	int radius;
public:
	HuntingState(Zombie*);
	virtual ~HuntingState() {}
	virtual void tick(Game* game);
	virtual void resolveObstacle(Game* game, Direction dir);
};
#endif