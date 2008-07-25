#include "huntingstate.h"
#include "globals.h"

HuntingState::HuntingState(Zombie* zombie) : BrainState(zombie) {
}

void HuntingState::tick(Game* game) {
	if (zombie->getLoc()->getDistance(*game->getPlayer()->getLoc()) > zombie->getSiteRadius()) {
		if (rand() % 100 < 50) {
			zombie->setCurrentAction(WANDERING);
		} 
	}
	Coord delta = *game->getPlayer()->getLoc() - *zombie->getLoc();
	Direction dx, dy;
	dx = (delta.getX() > 0) ? EAST : WEST;
	dy = (delta.getY() > 0) ? SOUTH : NORTH;

	Direction moveDir;
	
	double slope = 0;
	if (delta.getY()) {
		slope = (dx && dy) ? abs(delta.getX() / delta.getY()) : 0;
	}

	int offset;
	if (( slope > 0.7) && (slope < 1.3)) {
		int offset = (dx - EAST) ? 1 : -1;
		if (offset == -1 && dy == NORTH) {
			moveDir = NORTHWEST; 
		} else {
			moveDir = (Direction)(offset + dy);
		}
	} else {
		moveDir = (abs(delta.getX()) > abs(delta.getY())) ? dx : dy;
	}


	Coord targetBlock = *game->directionOffsets[moveDir] + *zombie->getLoc();
	if (!game->getMap()->getBlockAt(targetBlock.getX(), targetBlock.getY())->isPassable()
		&& targetBlock != *game->getPlayer()->getLoc()) {
		offset = rand() % 4 - 2;
		moveDir = (Direction)(moveDir + offset);
		if (moveDir == -2) {
			moveDir = WEST;
		} else if (moveDir == -1) {
			moveDir = NORTHWEST;
		} else if (moveDir == 8) {
			moveDir = NORTHEAST;
		} else if (moveDir == 9) {
			moveDir = EAST;
		}
	}


	zombie->queueMove(game->getTickcount() + zombie->getSpeed(), moveDir);
}

void HuntingState::resolveObstacle(Game* game, Direction dir) {
	if (rand() % 2) {
		//game->getReferee()->attackDirection(zombie, dir);
		Game::getInstance()->addEvent(EventFactory::createAttackEvent(zombie, dir, 0));
	}
}