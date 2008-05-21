#include "messagefactory.h"

Message* MessageFactory::getMessage(std::string &msg) {
	return new Message(&msg);
}

Message* MessageFactory::getItems(std::vector<Item*> items) {
	if (items.size() > 0) {
		std::string msg;
		msg = "On the ground lies ";
		
		msg += items.at(0)->getListName();
		for (unsigned int i = 1; i < items.size(); i++) {
			if (i == items.size() - 1) {
				msg += " and " + items.at(i)->getListName();
			} else {
				msg += ", " + items.at(i)->getListName();
			}
		}
		msg += ".";
		return new Message(msg.data());
	} else {
		return NULL;
	}
}