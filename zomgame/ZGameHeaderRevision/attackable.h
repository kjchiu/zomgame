#ifndef _ATTACKABLE_H_
#define _ATTACKABLE_H_

#include "all_includes.h"

class Attackable {
public:
	virtual Attribute* getHealth() = 0;
	virtual std::vector<Item*> destroy() = 0;
};

#endif