#include "move_event.h"
#include "game.h"
MoveEvent::MoveEvent() :
	Event(MOVE) {

}

MoveEvent::MoveEvent(Entity *_mover, Coord* _dest) :
	mover(_mover), destinationLoc(_dest), Event(MOVE) {
}

Message* MoveEvent::resolve(){
	if (!Game::getInstance()->getMap()->isWithinMap(destinationLoc)){
		return NULL;
	}
	MapBlock* target = Game::getInstance()->getMap()->getBlockAt(destinationLoc);
	MapBlock* start = Game::getInstance()->getMap()->getBlockAt(mover->getLoc());
	if (mover->getType() == Entity::PLAYER) {
		if (target->isPassable()){			
			start->removeEntity(start->getTopEntity());
			target->addEntity(mover);
			mover->setLoc(destinationLoc);
			Game::getInstance()->getTarget()->setCoord(mover->getLoc());
		} else if (target->hasProps() && dynamic_cast<Door*>(target->getTopProp())) {
			Game::getInstance()->addEvent(EventFactory::createInteractEvent(mover, destinationLoc, 0));

		} else if(target->hasEntities()) {
			Game::getInstance()->addEvent(EventFactory::createAttackEvent(mover, destinationLoc, 0));
		}
	} else if (mover->getType() == Entity::ZOMBIE) {
		if (target->isPassable()){			
			start->removeEntity(start->getTopEntity());
			target->addEntity(mover);
			mover->setLoc(destinationLoc);
		} else if (target->hasEntities() && target->getTopEntity()->getType() != Entity::ZOMBIE) {
			Game::getInstance()->addEvent(EventFactory::createAttackEvent(mover, destinationLoc, 0));
		}
	}
	return NULL;
}