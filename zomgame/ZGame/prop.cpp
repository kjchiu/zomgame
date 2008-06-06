#include "prop.h"

Prop::Prop(){
	durability = new Attribute("Durability", 100);
}

Prop::Prop(bool canPass) {
	setPassable(canPass);
	durability = new Attribute("Durability", 100);
}

Attribute* Prop::getDurability(){
	return durability;
}

int Prop::interact(Player *p){
	return 0;
}

bool Prop::isPassable(){
	return passable;
}

void Prop::setPassable(bool canPass){
	passable = canPass;
}

void Prop::initDurability(int value, int maxValue) {
	delete durability;
	durability = new Attribute(std::string("Durability"), value, maxValue);
}