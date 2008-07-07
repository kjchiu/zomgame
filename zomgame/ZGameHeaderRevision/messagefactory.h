#ifndef _MESSAGE_FACTORY_H
#define _MESSAGE_FACTORY_H

#include "all_includes.h"

class MessageFactory {
public:
	static Message* getMessage(std::string &msg);
	static Message* getInteractMessage(Entity* entity, Prop* prop);
	static Message* getDropItemMessage(Entity* entity, Item* item);
	static Message* getItems(std::vector<Item*> items);
};
#endif
