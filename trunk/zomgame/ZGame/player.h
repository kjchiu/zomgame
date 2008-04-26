/* Represents the player */
#include "map.h"
#include "entity.h"

class Player : public Entity{
	private:
		Coord* location;
		int maxHealth, curHealth;

	public:
		Player();
		int getCurHealth();
		int getMaxHealth();
		Coord* getLoc();
		void setCurHealth(int nCurHealth);
		void setMaxHealth(int nMaxHealth);
		void setLoc(Coord* nLocation);
		void draw(Map *map);
};