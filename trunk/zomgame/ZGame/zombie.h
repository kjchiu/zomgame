#ifndef _ZOMBIE_H
#define _ZOMBIE_H
#include "entity.h"
class Zombie : public Entity {
public:
	Zombie();
	void tick();

};

#endif