#ifndef _GRASS_H
#define _GRASS_H
#include <ctime>
class Grass : public Terrain {
public:
	Grass() {
		// , ; ` ' "
		int r = rand() % 5;
		switch(r) {
			case 0:
				displayChar = ',';
				break;
			case 4:
			case 1:
				displayChar = ';';
				break;
			case 2:
				displayChar = '\'';
				break;
			case 3:
				displayChar = '`';
				break;
		}
	}
	virtual ~Grass() {}
	virtual char getChar() { return ';'; }
	virtual short getColor() { return GREEN_BLACK; } // 
	virtual string getName() { return "grass"; }
	TerrainType getType() {return GRASS;}

};
#endif
