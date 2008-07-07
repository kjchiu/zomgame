#include "all_includes.h"

GetItemEvent::GetItemEvent(Entity* nPicker, Coord* nLoc, int nIndex) : Event(GET_ITEM){
	picker = nPicker;
	loc = nLoc;
	index = nIndex;
}

Message* GetItemEvent::resolve() {
	string* msgString = new string();
	Message* message = new Message(msgString);

	if (Game::getInstance()->getMap()->getBlockAt(loc)->getItems().size() == 0){
		*msgString = "There is nothing to pick up";
		return message;
	}
		
	Item* item = Game::getInstance()->getMap()->getBlockAt(loc)->getItemAt(index);
	Game::getInstance()->getMap()->getBlockAt(loc)->removeItem(item);
		
	//check for bulk
	picker->getInventory()->addItem(item);
	*msgString = "You pick up " + item->getListName();
	return message;
}