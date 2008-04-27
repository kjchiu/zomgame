/* This is a zombie, the walking dead, etc. */

#ifndef _ZOMBIE_H
#define _ZOMBIE_H
#include "entity.h"
class Zombie : public Entity {
public:
	Zombie();
	void tick(); //implements AI

};

#endif