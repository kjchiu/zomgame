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
struct SkillValue;

class Player : public Entity {
	protected:
		Coord* location;
		vector<SkillValue>* skills;
		Weapon* eqRngWeapon;
		
	public:
		Player();
		void equip(Weapon* weapon);
		Coord* getLoc();
		Weapon* getEqRngWeapon();
		void setLoc(Coord* nLocation);
		vector<SkillValue>* getSkills();
		int getSkillValue(int skill);
		void unequip(Weapon* weapon);
		void respawn(Coord* loc);
		void draw(Map *map);
};
#endif
