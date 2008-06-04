/* A prop, usually interactive, like a table, wall, chair, etc */

#ifndef _PROP_H
#define _PROP_H

#include <string>
#include "attribute.h"
#include "renderable.h"
//#include "player.h"

using namespace std;

class Player;

class Prop : public Renderable {

	private:
		bool passable; //passed in, dependent on the prop
		Attribute* durability;

	public:
		Prop();
		Prop(bool canPass);
		Attribute* getDurability();
		virtual void interact(Player* p);
		bool isPassable();
		void setPassable(bool canPass);
};

#endif
