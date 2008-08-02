/* Represents an attribute of the player, like strength, agility, etc. */

#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H

#include <string>
using namespace std;


enum Attributes{STRENGTH, HEALTH, STAMINA, THIRST, HUNGER, X};

class Attribute {

	private: 
		string name;
		int curValue, maxValue;
		Attributes type;
	public:
		Attribute();
		Attribute(string nName);
		Attribute(string nName, int nValue);
		Attribute(string nName, int nCurValue, int nMaxValue);
		Attribute(string nName, Attributes nType, int nCurValue, int nMaxValue);
		void init(string nName, Attributes nType, int nCurValue, int nMaxValue);
		void init(string nName, int nCurValue, int nMaxValue);
		string getName();
		Attributes getType();
		int getCurValue();
		int getMaxValue();
		int getPercentage();
		void setName(string nName);
		void setValue(int value);
		void changeCurValueBy(int change);
		void changeMaxValueBy(int change);
		//implement a function to raise the value
};

#endif