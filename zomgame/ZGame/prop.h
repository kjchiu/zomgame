/* A prop, usually interactive, like a table, wall, chair, etc */

#ifndef _PROP_H
#define _PROP_H

#include <string>
#include <vector>

#include "attribute.h"
#include "renderable.h"
#include "item.h"
//#include "propfactory.h"
//#include "player.h"

using namespace std;

class Player;

class Prop : public Renderable {

	private:
		bool seeThrough;
		bool passable; //passed in, dependent on the prop
		Attribute* durability;

	protected:
		void initDurability(int value, int maxValue);
		vector<Item*> debris;
	public:
		Prop();
		Prop(bool canPass);
		Attribute* getDurability();
		
		virtual bool isPassable();
		virtual bool isSeeThrough();
		
		virtual vector<Item*> destroy();
		virtual int interact(Player* p);
		
		void setSeeThrough(bool nSeeThrough);
		void setPassable(bool canPass);
		void setDebris(vector<Item*> &_debris);
};

#endif
