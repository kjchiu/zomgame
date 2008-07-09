#ifndef _INDOOR_TILE_H
#define _INDOOR_TILE_H
class IndoorTile : public Terrain {
public:
	IndoorTile() {setDisplayChar('#'); }
	virtual ~IndoorTile() {}

	TerrainType getType() {return INDOOR_TILE;}
};
#endif