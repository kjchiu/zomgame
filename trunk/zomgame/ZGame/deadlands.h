#ifndef _DEADLANDS_H
#define _DEADLANDS_H
class Deadlands : public Terrain {
public:
	Deadlands() {}
	virtual ~Deadlands() {}
	virtual char getChar() { return '-'; }
	virtual short getColor() { return 0; } // 
	virtual string getName() { return "dead.. DEAD!"; }
};
#endif