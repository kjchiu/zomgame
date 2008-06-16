#include "zombie.h"
#include "wanderstate.h"
#include "huntingstate.h"
#include <ctime>
#include "math.h"


Zombie::Zombie() : Entity(){
	if (rand() % 3 > 1) {
		color = 4;
		displayChar = 'z';
		setName("Uber Zombie");
		addAttribute(new Attribute("Health", 20));
		addAttribute(new Attribute("Strength", 15));
	} else  {
		color = 4;
		displayChar = 'Z';
		setName("Zombie");
		addAttribute(new Attribute("Health", 10));
		addAttribute(new Attribute("Strength", 5));
	}
	curAction = WANDERING;
	speed = 10;
	siteRadius = 20;
	brains = new BrainState*[num_states];
	brains[currentAction::NOTHING] = new BrainState(this);
	brains[currentAction::WANDERING] = new WanderState(this);
	brains[currentAction::HUNTING] = new HuntingState(this);

	colors = new short[num_states];
	colors[NOTHING] = color;
	colors[WANDERING] = color;
	colors[HUNTING] = 3;
	colors[INVESTIGATING] = 5;
}

int Zombie::getCurrentAction(){
	return curAction;
}

Coord* Zombie::getTarget(){
	return target;
}

short Zombie::getColor(){
	return colors[curAction];
}

// TODO: this needs to be dependent on time of day
int Zombie::getSiteRadius() {
	return siteRadius;
}

void Zombie::setCurrentAction(currentAction nAction){
	curAction = nAction;
	
}

void Zombie::setTarget(Coord* nTarget){
	target = nTarget;
}

void Zombie::queueMove(int time, Direction dir) {
	moveQueue.push_back(std::pair<int,Direction>(time,dir));
}

void Zombie::tick(Game* game) { //eat_brains()
	if (moveQueue.empty()) {
		brains[curAction]->tick(game);
	}
	
	while (!moveQueue.empty()) {
		if (moveQueue.front().first > game->getTickcount()) {
			break;
		} else {
			game->move(this, moveQueue.front().second);
			moveQueue.pop_front();
		}
	}

	if (this->getLoc()->getDistance(*game->getPlayer()->getLoc()) < getSiteRadius()) {
		if (rand() % 100 < 10) {
			curAction = currentAction::HUNTING;
		}
	}
}

void Zombie::resolveObstacle(Game* game, Direction dir) {
	brains[curAction]->resolveObstacle(game, dir);
}

void Zombie::respawn(Coord* c) {
	getAttribute("Health")->changeCurValueBy(20);
	curAction = WANDERING;
	this->setLoc(c);
}