/* This is a zombie, the walking dead, etc. */

#ifndef _ZOMBIE_H
#define _ZOMBIE_H

class Zombie;
class Game;

#include "game.h"
#include "entity.h"
#include "coord.h"

#include <string>

using namespace std;

class Zombie : public Entity {
public:
	enum currentAction {NOTHING, WANDERING, INVESTIGATING, HUNTING};

private:
	Coord* target; 
	currentAction curAction;

public:
	Zombie();
	int getCurrentAction();
	Coord* getTarget();
	void setCurrentAction(currentAction nAction);
	void setTarget(Coord* nTarget);
	void tick(Game* game); //implements AI

};

#endif