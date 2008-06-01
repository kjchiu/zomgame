#include "huntingstate.h"
#include "globals.h"

HuntingState::HuntingState(Zombie* zombie) : BrainState(zombie) {
}

void HuntingState::tick(Game* game) {
	if (zombie->getLoc()->getDistance(*game->getPlayer()->getLoc()) > zombie->getSiteRadius())
		if (rand() % 100 < 50) {
			zombie->setCurrentAction(WANDERING);
		} 
	Coord delta = *game->getPlayer()->getLoc() - *zombie->getLoc();
	Direction dx, dy;
	dx = (delta.getX() > 0) ? EAST : WEST;
	dy = (delta.getY() > 0) ? SOUTH : NORTH;
	Direction moveDir;
	double slope = (dx && dy) ? abs(delta.getX() / delta.getY()) : 0;
	if (dx && dy && (( slope > 0.7) || (slope < 1.3))) {
		int offset = (dx - EAST) ? 1 : -1;
		moveDir = (Direction)(offset + dy);
	} else {
		moveDir = (abs(delta.getX()) > abs(delta.getY())) ? dx : dy;
	}

	if (delta.getX() || delta.getY()) {
		zombie->queueMove(game->getTime() + zombie->getSpeed(), moveDir);
	}
}