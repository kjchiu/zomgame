#ifndef _WOOD_WALL_H
#define _WOOD_WALL_H
class WoodWall : public Terrain {
public:
	WoodWall() {}
	virtual ~WoodWall() {}
	virtual char getChar() { return 'X'; }
	virtual short getColor() { return 0; }
	virtual string getName() { return "Wooden Wall"; }

	TerrainType getType() {return WOOD_WALL;}
};
#endif