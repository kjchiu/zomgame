/* Produces props. */

#ifndef _PROPFACTORY_H
#define _PROPFACTORY_H

#include "door.h"
#include "prop.h"

class Prop;

class PropFactory {

	public:
		static Prop* createDoor();
		static Prop* createDoor(int durability);
		static Prop* createWall();
		static Prop* createWall(int durability);

};

#endif