#ifndef _PLAYER_H
#define _PLAYER_H
/* Represents the player */
#include "map.h"
#include "entity.h"
#include "skills.h"
#include <vector>
#include "globals.h"

struct Skill;
class SkillTable;

class Player : public Entity{
	protected:
		Coord* location;
		int maxHealth, curHealth;
		vector<int> skills;
	public:
		Player();
		int getCurHealth();
		int getMaxHealth();
		Coord* getLoc();
		void setCurHealth(int nCurHealth);
		void setMaxHealth(int nMaxHealth);
		void setLoc(Coord* nLocation);
		vector<int>* getSkills();
		void draw(Map *map);
};
#endif
