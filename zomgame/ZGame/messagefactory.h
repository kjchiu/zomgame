#ifndef _MESSAGE_FACTORY_H
#define _MESSAGE_FACTORY_H

#include "item.h"
#include "mapBlock.h"
#include "player.h"
#include "message.h"
#include <vector>

class MessageFactory {
public:
	static Message* getMessage(std::string &msg);
	static Message* getItems(std::vector<Item*> items);
};
#endif
