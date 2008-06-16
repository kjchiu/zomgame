#include "wanderstate.h"

WanderState::WanderState(Zombie* _zombie) : BrainState(_zombie){
	dir = SOUTH;
	wanderChance = 40;
}

void WanderState::tick(Game* game) {
	int chance = rand() % 100;
	if (chance < this->wanderChance) {
		int newdir = rand() % 4;
		switch(newdir) {
			case 0:
				dir = NORTH;
				break;
			case 1:
				dir = EAST;
				break;
			case 2:
				dir = SOUTH;
				break;
			case 3:
				dir = WEST;
				break;
		}
	}
	if (chance > 10)
		zombie->queueMove(game->getTickcount() + 20, dir);

}