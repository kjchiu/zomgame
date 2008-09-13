/* A prop that contains a number of items. */

#ifndef CONTAINER_H
#define CONTAINER_H

#include "prop.h"
#include "itemFactory.h"

class ContainerProp : public Prop {
	private:
		vector<Item*>* items;

	public:
		ContainerProp() {setName("Container"); setDisplayChar('='); setPassable(false);}
		int interact(Player* p);
		vector<Item*> destroy();
		void addItem(Item* item);
		void setItems(vector<Item*>* nItems);

};

#endif DOOR_H