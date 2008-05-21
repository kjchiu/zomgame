#include "zombie.h"
#include "wanderstate.h"
#include <ctime>


Zombie::Zombie() {
	if (rand() % 3 > 1) {
		color = 5;
		displayChar = 0x151;
		setName("Uber Zombie");
		addAttribute(new Attribute("Health", 20));
		addAttribute(new Attribute("Strength", 15));
	} else  {
		color = 5;
		displayChar = 'Z';
		setName("Zombie");
		addAttribute(new Attribute("Health", 10));
		addAttribute(new Attribute("Strength", 5));
	}
	curAction = WANDERING;
	
	brains = (BrainState*)malloc(sizeof(BrainState) * num_states);
	brains[0] = BrainState(this);
	brains[1] = WanderState(this);
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
	/*if (curAction == NOTHING){
//		game->addMessage(new Message("Zombie is lazy"));
		return;//?
	} else if (curAction == WANDERING) {
		string* msg = new string("Zombie is wandering");
		game->addMessage(new Message(msg));
		game->moveEntity(this, Game::NORTH);
	}*/
	//brains[curAction].tick(game);
}