#include "bed.h"

Bed::Bed(){
	init(5);
}

Bed::Bed(int nRValue){
	init(nRValue);
}

void Bed::init(int nRValue){
	setName("Bed");
	setDescription("A place to rest your eyes");
	setDisplayChar('=');
	setRValue(nRValue);
}

int Bed::getRValue(){
	return rValue;
}

void Bed::setRValue(int nRValue){
	if (nRValue > 10){ nRValue = 10;}
	if (nRValue < 1){ nRValue = 1;}
	rValue = nRValue;
}

int Bed::interact(Player* p){
	//set the player's status to sleeping

	return 10;
}

