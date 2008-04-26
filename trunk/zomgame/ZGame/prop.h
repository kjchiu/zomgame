/* A prop, usually interactive, like a table, wall, chair, etc */

#ifndef _PROP_H
#define _PROP_H

#include <string>

using namespace std;

class Prop {

	private:
		bool passable; //passed in, dependent on the prop
		string name;
		string description;
		int dispChar;

	public:
		Prop();
		bool isPassable();
		int getChar();
		string getDesc();
		string getName();
		void setChar(int nChar);
		void setDesc(string nDesc);
		void setName(string nName);
		void setPassable(bool canPass);
};

#endif
