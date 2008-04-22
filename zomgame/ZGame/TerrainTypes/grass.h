#ifndef _GRASS_H
#define _GRASS_H
class Grass : public Terrain {
public:
	Grass() {}
	virtual ~Grass() {}
	virtual char getChar() { return ';'; }
	virtual short getColor() { return 1; } // 
	virtual string getName() { return "grass"; }

};
#endif