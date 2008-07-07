/* This is a zombie, the walking dead, etc. */

#ifndef _ZOMBIE_H
#define _ZOMBIE_H

class Game;
class Zombie;

#include "game.h"
#include "entity.h"
#include "coord.h"
#include "direction.h"
#include "item.h"

#include <string>
#include <deque>

using namespace std;



class BrainState {
protected:
	Zombie* zombie;
public:
	BrainState(Zombie* _zombie) {zombie = _zombie;}
	virtual ~BrainState() {}
	virtual void tick(Game* game) {};
	virtual void resolveObstacle(Game* game, Direction dir) {}
};


enum currentAction {NOTHING, WANDERING, INVESTIGATING, HUNTING};

class Zombie : public Entity {
private:
	friend class BrainState;

protected:
	Coord* target;
	currentAction curAction;
	BrainState** brains;
	short* colors;
	static const int num_states = 4;
	std::deque<std::pair<int,Direction> > moveQueue;

public:
	Zombie();
	int getCurrentAction();
	Coord* getTarget();
	void setCurrentAction(currentAction nAction);
	void setTarget(Coord* nTarget);
	void tick(Game* game); //implements AI
	void resolveObstacle(Game* game, Direction dir);
	void queueMove(int time, Direction dir);
	virtual int getSiteRadius();
	virtual short getColor();
	virtual void respawn(Coord* c);

	// implements Attackable
	virtual std::vector<Item*> destroy();
};



#endif
