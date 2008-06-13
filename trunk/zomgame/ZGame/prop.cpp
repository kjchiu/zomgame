#include "prop.h"

Prop::Prop(){
	setSeeThrough(true);
	setPassable(true);
	durability = new Attribute("Durability", 100);
}

Prop::Prop(bool canPass) {
	setPassable(canPass);
	setSeeThrough(true);
	durability = new Attribute("Durability", 100);
}

Attribute* Prop::getDurability(){
	return durability;
}

void Prop::destroy(){

}

int Prop::interact(Player *p){
	return 0;
}

bool Prop::isPassable(){
	return passable;
}

bool Prop::isSeeThrough(){
	return seeThrough;
}

void Prop::setPassable(bool canPass){
	passable = canPass;
}

void Prop::setSeeThrough(bool nSeeThrough){
	seeThrough = nSeeThrough;
}

void Prop::initDurability(int value, int maxValue) {
	delete durability;
	durability = new Attribute(std::string("Durability"), value, maxValue);
}