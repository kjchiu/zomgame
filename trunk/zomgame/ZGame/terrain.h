/* Represents a terrain type */

#include <string>

using namespace std;

virtual class Terrain {
	public:
		virtual ~Terrain(){};
		virtual char getChar();
		virtual string getName();
};