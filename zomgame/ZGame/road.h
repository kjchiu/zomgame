#ifndef _ROAD_H
#define _ROAD_H
class Road : public Terrain {
public:
	Road() {setDisplayChar(ACS_CKBOARD); setColor(2);}
	virtual ~Road() {}

	TerrainType getType() {return ROAD;}
};
#endif