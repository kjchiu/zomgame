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
	brains[NOTHING] = new BrainState(this);
	brains[WANDERING] = new WanderState(this);
	brains[HUNTING] = new HuntingState(this);

	colors = new short[num_states];
	colors[NOTHING] = color;
	colors[WANDERING] = color;
	colors[HUNTING] = 3;
	colors[INVESTIGATING] = 5;

	this->setType(Entity::ZOMBIE);
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
		if (static_cast<unsigned int>(moveQueue.front().first) > game->getTickcount()) {
			break;
		} else {
			//if (game->getMap()->getBlockAt(&(*getLoc() + *game->directionOffsets[(int)moveQueue.front().second]))->isPassable()) {
				game->addEvent(EventFactory::createMoveEvent(this, moveQueue.front().second, 0));
			//} else {
			//	resolveObstacle(game, moveQueue.front().second);
			//}
			moveQueue.pop_front();
		}
	}

	if (this->getLoc()->getDistance(*game->getPlayer()->getLoc()) < getSiteRadius()) {
		if (rand() % 100 < 10) {
			curAction = HUNTING;
		}
	}
}

void Zombie::resolveObstacle(Game* game, Direction dir) {
	brains[curAction]->resolveObstacle(game, dir);
}

void Zombie::respawn(Coord* c) {
	setLoc(c);
    getAttribute("Health")->changeCurValueBy(20);
    curAction = WANDERING;
   // Game::getInstance()->getMap()->getBlockAt(getLoc())->addEntity(this);
	Game::getInstance()->addEvent(EventFactory::createSpawnEntityEvent(this, c, 0));
	
}

std::vector<Item*> Zombie::destroy() {
	int x, y;
	x = rand() % Game::getInstance()->getMap()->getWidth();
	y = rand() % Game::getInstance()->getMap()->getHeight();
	Coord *c = new Coord(x,y);
//	do {
//		c = new Coord(x,y);
//	} while (Game::getInstance()->getMap()->getBlockAt(c)->hasEntities());
	respawn(c);

	//curAction = WANDERING;
	//Game::getInstance()->addEvent(EventFactory::createSpawnEntityEvent(this, c, 0));
	
	// Fear their woody innards.
	std::vector<Item*> debris;
	//debris.push_back(ItemFactory::createWoodPlank());
	return debris;
}
