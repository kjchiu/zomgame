#ifndef TERRAIN_FACTORY_H
#define TERRAIN_FACTORY_H

#include "all_includes.h"

class TerrainFactory
{
public:
	static Terrain* makeTerrain(TerrainType type);
};

#endif