/* A weapon in the game. Inherits from Item, and has some properties in addition to it. */

#include "item.h"
#include <string>

using namespace std;

class Weapon : public Item {
	
	private:
		string wClass; //relates to what skill is associated with the weapon
		int damage;
		int curDurability;
		int maxDurability; //likely always going to have 100, maybe this can be modified?

	public:
		Weapon();
		string getWClass();
		int getCurDur();
		int getDamage();
		int getMaxDur();
		void setWClass(string nClass);
		void setCurDur(int nCurD);	
		void setDamage(int nDmg);
		void setMaxDur(int nMaxD);
		
		
};