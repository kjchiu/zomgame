#ifndef _PLAYER_H
#define _PLAYER_H
/* Represents the player */
#include "map.h"
#include "entity.h"
#include "skills.h"
#include <vector>
#include "globals.h"
#include "weapon.h"

struct Skill;
class SkillTable;

class Player : public Entity{
	protected:
		Coord* location;
		vector<int> skills;
		
	public:
		Player();
		Coord* getLoc();
		void setLoc(Coord* nLocation);
		vector<int>* getSkills();
		void draw(Map *map);
};
#endif
