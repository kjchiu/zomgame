#include "attribute_factory.h"

Attribute* AttributeFactory::getStrength() {

	return new Attribute("Strength", STRENGTH, 10, 10);
}

Attribute* AttributeFactory::getHealth() {
	return AttributeFactory::getHealth(10);
}

Attribute* AttributeFactory::getHealth(int health) {
	return new Attribute("Health", HEALTH, health, health);
}

Attribute* AttributeFactory::getStamina() {
	return new Attribute("Stamina", STAMINA, 1000, 1000);
}

Attribute* AttributeFactory::getHunger() {
	return new Attribute("Hunger", HUNGER, 1000, 1000);
}

Attribute* AttributeFactory::getThirst() {
	return new Attribute("Thirst", THIRST, 1000, 1000);
}