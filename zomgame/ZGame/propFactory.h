/* Produces props. */

#ifndef _PROPFACTORY_H
#define _PROPFACTORY_H

#include "door.h"
#include "bed.h"
#include "container_prop.h"
#include "prop.h"

class PropFactory {

	public:
		static Bed* createBed();
		static Bed* createBed(int nRValue);
		static Door* createDoor();
		static Door* createDoor(int durability);
		static Prop* createWall();
		static Prop* createWall(int durability);
		static ContainerProp* createContainer(vector<Item*>* items);
		static ContainerProp* createContainer();

};

#endif