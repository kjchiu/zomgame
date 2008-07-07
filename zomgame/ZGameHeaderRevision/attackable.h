#ifndef _ATTACKABLE_H_
#define _ATTACKABLE_H_

#include <vector>
#include <string>

#include "attribute.h"
#include "item.h"

class Attackable {
public:
	virtual Attribute* getHealth() = 0;
	virtual std::vector<Item*> destroy() = 0;
};

#endif