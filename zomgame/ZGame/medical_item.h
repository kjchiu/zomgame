/* Any medical items, like bandages, first aid kits, and...hypodermics or something are medical items. */

#ifndef _MEDICALITEM_H
#define _MEDICALITEM_H

#include "item.h"

class MedicalItem : public Item {
	private:
		int healPotential; // from 1 to 10, 1 being the lowest and 10 being the highest
			//note: the higher the healing potential, the greater chance of failure

	public:
		MedicalItem();
		MedicalItem(string name, int potential);
		int getHealPot();
		void setHealPot(int nHealPotential);
};

#endif