/* Represents an attribute of the player, like strength, agility, etc. */

#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H

#include <string>
using namespace std;

class Attribute {

	private: 
		string name;
		int curValue, maxValue;
	public:
		Attribute();
		Attribute(string nName);
		Attribute(string nName, int nValue);
		Attribute(string nName, int nCurValue, int nMaxValue);
		void init(string nName, int nCurValue, int nMaxValue);
		string getName();
		int getCurValue();
		int getMaxValue();
		void setName(string nName);
		void setValue(int value);
		void changeCurValueBy(int change);
		void changeMaxValueBy(int change);
		//implement a function to raise the value
};

#endif