#ifndef _WHEAT_H
#define _WHEAT_H
class Wheat : public Terrain {
public:
	Wheat() {setDisplayChar(';'); setColor(4);}
	virtual ~Wheat() {}

	TerrainType getType() {return WHEAT;}
};
#endif