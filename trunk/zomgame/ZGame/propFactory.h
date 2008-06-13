/* Produces props. */

#ifndef _PROPFACTORY_H
#define _PROPFACTORY_H

#include "door.h"
#include "prop.h"

class PropFactory {

	public:
		static Door* createDoor();
		static Door* createDoor(int durability);
		static Prop* createWall();
		static Prop* createWall(int durability);

};

#endif