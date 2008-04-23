/* Represents the player */
#include "coord.h"
#include "map.h"
#include "entity.h"

class Player : public Entity{
	private:
		Coord* location;

	public:
		Player();
		Coord* getLoc();
		void setLoc(Coord* nLocation);
		void draw(Map *map);
};