/* This is a usable, pick-up-able item */

#ifndef _ITEM_H
#define _ITEM_H

#include "renderable.h"
#include <vector>

using namespace std;

class Item : public Renderable {

	public:
		enum ItemType {NOTYPE, FOOD, WEAPON, CONTAINER, AMMO, MATERIAL};	
		
	private:
		int bulk; //might use this
		int weight;
		ItemType type; //determines what type of item this is
		vector<int>* associatedSkills;
		static int id;
		int thisID;
		
	public:
		Item();
		void addSkill(int skillNum);
		int getBulk();
		int getID() const;
		int getType();
		string getTypeString();
		int getWeight();	
		vector<int>* getSkills();
		void removeSkill(int skillNum);
		void setBulk(int nBulk);
		void setType(ItemType nType);
		void setWeight(int nWeight);
		bool operator==(const Item&) const;


};

#endif