#include "zombie.h"
#include <ctime>

Zombie::Zombie() {
	if (rand() % 3 > 1) {
		color = 5;
		displayChar = 0x151;
		setName("Uber Zombie");
	} else  {
		color = 1;
		displayChar = 'Z';
		setName("Zombie");
	}
	curAction = NOTHING;
}

int Zombie::getCurrentAction(){
	return curAction;
}

Coord* Zombie::getTarget(){
	return target;
}

void Zombie::setCurrentAction(currentAction nAction){
	curAction = nAction;
}

void Zombie::setTarget(Coord* nTarget){
	target = nTarget;
}

void Zombie::tick(Game* game) { //eat_brains()
	if (curAction == NOTHING){
//		game->addMessage(new Message("Zombie is lazy"));
		return;//?
	} else if (curAction == WANDERING) {
		string* msg = new string("Zombie is wandering");
		game->addMessage(new Message(msg));
		game->moveEntity(this, Game::NORTH);
	}
}