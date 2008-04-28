/* This is a vector of items that will be on each entity. */

#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <vector>

#include "item.h"

using namespace std;

class Inventory {
	
	private:
		vector <Item*> items;
		int totalBulk;
		int totalWeight;
		
	public:
		Inventory();
		bool addItem(Item* item);
		int getTotalBulk();	
		int getTotalWeight();
		bool removeItem(Item* item);
};

#endif