#include "huntingstate.h"

HuntingState::HuntingState(Zombie* zombie) : BrainState(zombie) {
}

void HuntingState::tick(Game* game) {
	Coord delta = *game->getPlayer()->getLoc() - *zombie->getLoc();
	Direction dx, dy;
	dx = (delta.getX() > 0) ? Direction::EAST : Direction::WEST;
	dy = (delta.getY() > 0) ? Direction::SOUTH : Direction::NORTH;
	Direction dir = (abs(delta.getX()) > abs(delta.getY())) ? dx : dy;
	if (delta.getX() || delta.getY())
		zombie->queueMove(game->getTime() + zombie->getSpeed(), dir);
}