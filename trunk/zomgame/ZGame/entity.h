/* This represents an NPC, whether friendly or hostile (person or living, walking corpse) */

#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>
#include "coord.h"

using namespace std;

class Entity {
	protected:
		int thisID;
		string name;
		string desc;
		char displayChar;
		short color;
		Coord* location;

	public:
		static int id;

		Entity();
		virtual string getDescription();
		virtual char getDisplayChar();
		virtual int getID();
		virtual short getColor();
		virtual Coord* getLoc();
		virtual string getName();
		virtual void setLoc(Coord* nLocation);
		virtual void setName(string newName);
		virtual void setDescription(string newDesc);
		virtual void setDisplayChar(char newDispChar);
		virtual void setColor(short newColor);
};

//

#endif