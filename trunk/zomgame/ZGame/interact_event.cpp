#include "interact_event.h"
#include "game.h"

InteractEvent::InteractEvent(Entity* _actor, Coord* _loc)
: actor(_actor), loc(_loc), Event(INTERACT) {
}

Message* InteractEvent::resolve() {
	Prop* prop = Game::getInstance()->getMap()->getBlockAt(loc)->getTopProp();
	prop->interact(static_cast<Player*>(actor));
	return MessageFactory::getInteractMessage(actor, prop);		
}