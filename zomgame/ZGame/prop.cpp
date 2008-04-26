#include "prop.h"

Prop::Prop(){
	
}

bool Prop::isPassable(){
	return passable;
}

int Prop::getChar(){
	return dispChar;
}

string Prop::getDesc(){
	return description;
}

string Prop::getName(){
	return name;
}

void Prop::setChar(int nChar){
	dispChar = nChar;
}

void Prop::setDesc(string nDesc){
	description = nDesc;
}

void Prop::setName(string nName){
	name = nName;
}

void Prop::setPassable(bool canPass){
	passable = canPass;
}