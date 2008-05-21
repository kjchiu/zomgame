/* This is a zombie, the walking dead, etc. */

#ifndef _ZOMBIE_H
#define _ZOMBIE_H

class Game;
class Zombie;

#include "game.h"
#include "entity.h"
#include "coord.h"


#include <string>

using namespace std;

class BrainState {
protected:
	Zombie* zombie;
public:
	BrainState(Zombie* _zombie) {zombie = _zombie;}
	virtual ~BrainState() {}
	virtual void tick(Game* game) {};
};


class Zombie : public Entity {
public:
	enum currentAction {NOTHING, WANDERING, INVESTIGATING, HUNTING};

protected:
	Coord* target; 
	currentAction curAction;
	BrainState* brains;
	static const int num_states = 4;

public:
	Zombie();
	int getCurrentAction();
	Coord* getTarget();
	void setCurrentAction(currentAction nAction);
	void setTarget(Coord* nTarget);
	void tick(Game* game); //implements AI

	

};



#endif