#include "prop.h"

Prop::Prop(){
	setSeeThrough(true);
	setPassable(true);
	health = new Attribute("Health", 100);
}

Prop::Prop(bool canPass) {
	setPassable(canPass);
	setSeeThrough(true);
	health = new Attribute("Health", 100);
}

Attribute* Prop::getHealth(){
	return health;
}

vector<Item*> Prop::destroy(){
	return debris;
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

void Prop::setDebris(vector<Item*> &_debris) {
	debris = _debris;
}

void Prop::initHealth(int value, int maxValue) {
	delete health;
	health = new Attribute(std::string("Durability"), value, maxValue);
}