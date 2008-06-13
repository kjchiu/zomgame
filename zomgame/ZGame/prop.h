/* A prop, usually interactive, like a table, wall, chair, etc */

#ifndef _PROP_H
#define _PROP_H

#include <string>
#include "attribute.h"
#include "renderable.h"
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
	public:
		Prop();
		Prop(bool canPass);
		Attribute* getDurability();
		
		virtual bool isPassable();
		virtual bool isSeeThrough();
		
		virtual void destroy();
		virtual int interact(Player* p);
		
		void setSeeThrough(bool nSeeThrough);
		void setPassable(bool canPass);
};

#endif
