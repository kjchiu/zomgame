/* This represents an NPC, whether friendly or hostile (person or living, walking corpse) */

#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>

using namespace std;

class Entity {
	protected:
		int thisID;
		string name;
		string desc;
		char displayChar;
		short color;

	public:
		static int id;

		Entity();
		virtual string getDescription();
		virtual char getDisplayChar();
		virtual int getID();
		virtual short getColor();
		virtual string getName();
		virtual void setName(string newName);
		virtual void setDescription(string newDesc);
		virtual void setDisplayChar(char newDispChar);
		virtual void setColor(short newColor);
};

//

#endif