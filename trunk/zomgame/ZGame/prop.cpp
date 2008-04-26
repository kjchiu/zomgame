#include "prop.h"

Prop::Prop(){
	
}

Prop::Prop(bool canPass) {
	setPassable(canPass);
}

bool Prop::isPassable(){
	return passable;
}

void Prop::setPassable(bool canPass){
	passable = canPass;
}