/* This is a usable, pick-up-able item */

#ifndef _ITEM_H
#define _ITEM_H

#include "renderable.h"

class Item : public Renderable {

	private:
		int bulk; //might use this
		int weight;
		
	public:
		Item();
		int getBulk();
		int getWeight();
		void setBulk(int nBulk);
		void setWeight(int nWeight);
};

#endif