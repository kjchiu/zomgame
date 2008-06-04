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

void Prop::interact(Player *p){

}

bool Prop::isPassable(){
	return passable;
}

void Prop::setPassable(bool canPass){
	passable = canPass;
}