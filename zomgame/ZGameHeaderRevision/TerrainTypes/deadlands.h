#ifndef _DEADLANDS_H
#define _DEADLANDS_H
#include "curses.h"

class Deadlands : public Terrain {
public:
	Deadlands() {setDisplayChar(ACS_CKBOARD); setColor(1);}
	virtual ~Deadlands() {}

	TerrainType getType() {return DEADLANDS;}
};
#endif