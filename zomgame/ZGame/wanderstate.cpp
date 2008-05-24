#include "wanderstate.h"

WanderState::WanderState(Zombie* _zombie) : BrainState(_zombie){
	dir = Game::SOUTH;
	wanderChance = 40;
}

void WanderState::tick(Game* game) {
	int chance = rand() % 100;
	if (chance < this->wanderChance) {
		int newdir = rand() % 4;
		switch(newdir) {
			case 0:
				dir = Game::NORTH;
				break;
			case 1:
				dir = Game::EAST;
				break;
			case 2:
				dir = Game::SOUTH;
				break;
			case 3:
				dir = Game::WEST;
				break;
		}
	}
	game->moveEntity(zombie, dir);

}