#ifndef _ATTRIBUTE_FACTORY_H_
#define _ATTRIBUTE_FACTORY_H_

#include "attribute.h"



class AttributeFactory {
public:
	static Attribute* getStrength();
	static Attribute* getHealth();
	static Attribute* getHealth(int health);
	static Attribute* getStamina();
	static Attribute* getThirst();
	static Attribute* getHunger();
};

#endif