/* Represents a terrain type */

#include <string>

using namespace std;

class Terrain {
	public:
		/*virtual ~Terrain(){};
		virtual char getChar() {
			return '-';
		}
		virtual short getColor() {
			return 0;
		}
		virtual string getName() {
			return "wtf";
		}*/

		virtual ~Terrain() {}
		virtual char getChar() = 0;
		virtual short getColor() = 0;
		virtual string getName() = 0;
};