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
		char displayChar;
		string name;
		
	public:
		virtual short getColor() {return color;}
		virtual string getDescription() {return desc;}
		virtual char getDisplayChar() {return displayChar;}
		virtual string getName() {return name;}
		virtual void setName(string newName) {name = newName;}
		virtual void setDescription(string newDesc) {desc = newDesc;}
		virtual void setDisplayChar(char newDispChar) {displayChar = newDispChar;}
		virtual void setColor(short newColor) {color = newColor;}

};

#endif