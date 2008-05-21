#include "attribute.h"

Attribute::Attribute(){
	init("Attribute", 1, 1);
}

Attribute::Attribute(string nName){
	init(nName, 1, 1);
}

Attribute::Attribute(string nName, int nValue){
	init(nName, nValue, nValue);
}

Attribute::Attribute(string nName, int nCurValue, int nMaxValue){ 
	init(nName, nCurValue, nMaxValue);
}

void Attribute::init(string nName, int nCurValue, int nMaxValue){
	setName(nName);
	curValue = nCurValue;
	maxValue = nMaxValue;
}

string Attribute::getName(){
	return name;
}

int Attribute::getCurValue(){
	return curValue;
}

int Attribute::getMaxValue(){
	return maxValue;
}

void Attribute::setName(string nName){
	name = nName;
}

void Attribute::changeCurValueBy(int change){
	if (curValue + change < 1){
		curValue = 0;
		return;
	}
	if (curValue + change > maxValue){ 
		curValue = maxValue;
		return;
	}
	curValue += change;
}

void Attribute::changeMaxValueBy(int change){
	if (maxValue + change < 1){
		curValue = 1;
		maxValue = 1;
		return;
	}
	maxValue += change;
	changeCurValueBy(change);
}