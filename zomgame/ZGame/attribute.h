/* Represents an attribute of the player, like strength, agility, etc. */

#include <string>

using namespace std;

class Attribute {

	private: 
		string name;
		int value;

	public:
		Attribute();
		Attribute(string nName);
		Attribute(string nName, int nValue);
		void init(string nName, int nValue);
		string getName();
		int getValue();
		void setName(string nName);
		void setValue(int nValue);
		//implement a function to raise the value
};