#include "drop_item_event.h"
#include "game.h"

DropItemEvent::DropItemEvent(Entity* _actor, int _index) 
:	actor(_actor), index(_index), Event(DROP_ITEM) {
}

Message* DropItemEvent::resolve() {
	Item* item = actor->getInventory()->getItemAt(index);
	actor->getInventory()->removeItemAt(index);
	Game::getInstance()->getMap()->getBlockAt(actor->getLoc())->addItem(item);
	return MessageFactory::getDropItemMessage(actor, item);
}