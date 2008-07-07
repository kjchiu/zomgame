#ifndef TERRAIN_H
#define TERRAIN_H
/* Represents a terrain type */

#include <string>
#include "renderable.h"

using namespace std;

enum TerrainType
{
	UNKNOWN = 0,
	GRASS = 1,
	DEADLANDS,
	WHEAT,
	WOOD_WALL,
	INDOOR_TILE
};

class Terrain : public Renderable {
	public:
		virtual TerrainType getType()
		{
			return UNKNOWN;
		}
		virtual ~Terrain() {}
};

#endif