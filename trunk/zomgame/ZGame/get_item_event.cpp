#include "get_item_event.h"
#include "game.h"

GetItemEvent::GetItemEvent(Entity* nPicker, Coord* nLoc, int nIndex) : Event(GET_ITEM){
	picker = nPicker;
	loc = nLoc;
	index = nIndex;
}

Message* GetItemEvent::resolve() {
	string* msgString = new string();
	Message* message = new Message(msgString);

	if (Game::getInstance()->getRightInvList()->size() == 0){
		*msgString = "There is nothing to pick up";
		return message;
	}
		
	Item* item = Game::getInstance()->getRightInvList()->at(index);
	vector<Item*>* items = Game::getInstance()->getRightInvList();
	for (unsigned int i=0; i<items->size(); i++){
		if (items->at(i)->getID() == item->getID()){
			if (i==items->size()-1){
				items->pop_back();
			} else {
				items->erase(items->begin()+i, items->begin()+i+1); 
			} 
		}
	}
		
	//check for bulk
	picker->getInventory()->addItem(item);
	*msgString = "You pick up " + item->getListName();
	return message;
}