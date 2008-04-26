/* This represents an NPC, whether friendly or hostile (person or living, walking corpse) */

#ifndef _ENTITY_H
#define _ENTITY_H

#include "renderable.h"

using namespace std;

class Entity : public Renderable {
	protected:
		static int id;
		int thisID;
		Coord* location;
		
	public:
		Entity();
		Entity(string name);
		virtual int getID();
		virtual Coord* getLoc();
		virtual void setLoc(Coord* nLocation);
		
};

#endif