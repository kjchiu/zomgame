#ifndef _PLAYER_H
#define _PLAYER_H
/* Represents the player */

#include "all_includes.h"

class Skill;
struct SkillValue;

class Item;

class Player : public Entity {
	protected:
		Coord* location;
		vector<SkillValue>* skills;
		Weapon* eqRngWeapon;
		
	public:
		Player();
		void equip(Weapon* weapon);
		void exert(int exertion); //lowers thirst, hunger, and stamina
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
