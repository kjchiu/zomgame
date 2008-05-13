#include "attribute.h"

Attribute::Attribute(){
	init("Attribute", 0);
}

Attribute::Attribute(string nName){
	init(nName, 0);
}

Attribute::Attribute(string nName, int nValue){
	init(nName, nValue);
}

void Attribute::init(string nName, int nValue){
	setName(nName);
	setValue(nValue);
}

string Attribute::getName(){
	return name;
}

int Attribute::getValue(){
	return value;
}

void Attribute::setName(string nName){
	name = nName;
}

void Attribute::setValue(int nValue){
	value = nValue;
}