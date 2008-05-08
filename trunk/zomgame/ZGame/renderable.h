/* This is a virtual class that any class will extend if it will be rendered on screen */

#ifndef _RENDERABLE_H
#define _RENDERABLE_H

#include <string>
#include "coord.h"

using namespace std;

class Renderable {
	protected:
		short color;
		string desc;
		unsigned long displayChar;
		string name;
		static int id;
		int thisID;
		
	public:
		Renderable(){thisID = ++id;}
		virtual short getColor() {return color;}
		virtual string getDescription() {return desc;}
		virtual long getDisplayChar() {return displayChar;}
		virtual int getID() {return thisID;}
		virtual string getListName();
		virtual string getName() {return name;}
		virtual void setName(string newName) {name = newName;}
		virtual void setDescription(string newDesc) {desc = newDesc;}
		virtual void setDisplayChar(unsigned long newDispChar) {displayChar = newDispChar;}
		virtual void setColor(short newColor) {color = newColor;}

};

#endif