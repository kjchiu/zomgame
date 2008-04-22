/* This represents an NPC, whether friendly or hostile (person or living, walking corpse) */

#ifndef _ENTITY_H
#define _ENTITY_H

#include <string>

using namespace std;

class Entity {
	private:
		int thisID;
		string name;
		string desc;
		char displayChar;

	public:
		static int id;

		Entity();
		string getDescription();
		char getDisplayChar();
		int getID();
		string getName();
		void setName(string newName);
		void setDescription(string newDesc);
		void setDisplayChar(char newDispChar);
};

//

#endif