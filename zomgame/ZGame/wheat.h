#ifndef _WHEAT_H
#define _WHEAT_H
class Wheat : public Terrain {
public:
	Wheat() {}
	virtual ~Wheat() {}
	virtual char getChar() { return ';'; }
	virtual short getColor() { return 4; } // 
	virtual string getName() { return "wheat"; }

};
#endif