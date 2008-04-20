/* Represents the player */
#include "coord.h"
#include "map.h"

class Player {
	private:
		char* name; 
		Coord* location;

	public:
		Player();
		Coord* getLoc();
		char* getName();
		void setLoc(Coord* nLocation);
		void setName(char* nName);
		void draw(Map *map);
};