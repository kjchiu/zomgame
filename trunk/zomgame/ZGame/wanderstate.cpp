#include "wanderstate.h"

WanderState::WanderState(Zombie* _zombie) : BrainState(_zombie){
	dir = Game::SOUTH;
}

void WanderState::tick(Game* game) {
	if (rand() % 100 < this->wanderChance) {
		switch(rand() % 4) {
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