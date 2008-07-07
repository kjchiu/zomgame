/* A bed, but technically any resting space such as a pile of hay */

/* Gameplay: A player can recover stamina by resting, but sleeping is a much more effective way, at the cost of security */

#ifndef _BED_H
#define _BED_H

#include "prop.h"

class Bed: public Prop {

	private:
		int rValue; //recovery value: how restful the bed is. Ranges from 1 to 10

	public:
		Bed();
		Bed(int nRValue);
		void init(int nRValue);

		int getRValue();
		void setRValue(int nRValue);
		
		int interact(Player* p); //change the player status to 'sleeping'

};

#endif