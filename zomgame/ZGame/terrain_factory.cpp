#include "terrain_factory.h"
#include "TerrainTypes/terrain_types.h"

Terrain* TerrainFactory::makeTerrain(TerrainType type)
{
	Terrain *terrain = NULL;
	switch(type)
	{
	case GRASS:
		terrain = new Grass;
		break;
	case DEADLANDS:
		terrain = new Deadlands;
		break;
	case WHEAT:
		terrain = new Wheat;
		break;
	case WOOD_WALL:
		terrain = new WoodWall;
		break;
	case INDOOR_TILE:
		terrain = new IndoorTile;
		break;
	case ROAD:
		terrain = new Road;
		break;
	default:
		terrain = new Terrain;
		break;
	}
	return terrain;
}