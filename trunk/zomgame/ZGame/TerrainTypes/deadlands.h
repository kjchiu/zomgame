#ifndef _DEADLANDS_H
#define _DEADLANDS_H
class Deadlands : public Terrain {
public:
	Deadlands() {setDisplayChar('-'); setColor(1);}
	virtual ~Deadlands() {}
};
#endif