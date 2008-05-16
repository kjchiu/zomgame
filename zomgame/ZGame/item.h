/* This is a usable, pick-up-able item */

#ifndef _ITEM_H
#define _ITEM_H

#include "renderable.h"
#include <vector>

using namespace std;

class Item : public Renderable {

	public:
		enum ItemType {NOTYPE, FOOD, WEAPON, CONTAINER};	
		
	private:
		int bulk; //might use this
		int weight;
		ItemType type; //determines what type of item this is
		string typeNames[4];
		vector<int>* associatedSkills;
		
	public:
		Item();
		void addSkill(int skillNum);
		int getBulk();
		string getType();
		int getWeight();	
		vector<int>* getSkills();
		void setBulk(int nBulk);
		void setType(ItemType nType);
		void setWeight(int nWeight);


};

#endif