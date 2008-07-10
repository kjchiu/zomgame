#include "medical_item.h"

MedicalItem::MedicalItem(){
	setName("Bandage");
	setHealPot(1);
	setDescription("You should be able to use this to heal your wounds");
	setDisplayChar('+');
}

MedicalItem::MedicalItem(string name, int nHealPotential){
	setName(name);
	setHealPot(nHealPotential);
	setDescription("You should be able to use this to heal your wounds");
	setDisplayChar('+');
}

int MedicalItem::getHealPot(){
	return healPotential;
}

void MedicalItem::setHealPot(int nHealPotential){
	if (nHealPotential > 10){
		healPotential = 10;	
	} else if (nHealPotential < 1){
		healPotential = 1;
	} else {
		healPotential = nHealPotential;
	}

}