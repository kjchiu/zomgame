/* This is a usable, pick-up-able item */

#ifndef _ITEM_H
#define _ITEM_H

#include "renderable.h"

class Item : public Renderable {

	private:
		int bulk; //might use this
		int weight;
		string type; //determines what type of item this is
		
	public:
		Item();
		int getBulk();
		string getType();
		int getWeight();	
		void setBulk(int nBulk);
		void setType(string nType);
		void setWeight(int nWeight);
};

#endif