/* Represents the player */
#include "coord.h"
#include "map.h"
#include "entity.h"

class Player : public Entity{
	private:
		//char* name; 
		Coord* location;

	public:
		Player();
		Coord* getLoc();
		//char* getName();
		//string getName();
		void setLoc(Coord* nLocation);
		//void setName(char* nName);
		void draw(Map *map);
};