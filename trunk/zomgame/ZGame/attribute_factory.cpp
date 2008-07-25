#include "attribute_factory.h"

Attribute* AttributeFactory::getStrength() {

	return new Attribute("Strength", STRENGTH, 10, 100);
}

Attribute* AttributeFactory::getHealth() {
	return AttributeFactory::getHealth(10);
}

Attribute* AttributeFactory::getHealth(int health) {
	return new Attribute("Health", HEALTH, health, health);
}

Attribute* AttributeFactory::getStamina() {
	return new Attribute("Stamina", STAMINA, 100, 100);
}