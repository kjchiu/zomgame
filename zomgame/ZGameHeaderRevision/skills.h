#ifndef _SKILLS_H
#define _SKILLS_H

#include <string>

#include "skilltable.h"
#include "player.h"
#include "message.h"
#include "messagefactory.h"
//#include "boost/filesystem.hpp"

enum SkillType {PASSIVE, ACTIVE};
#define TARGET_ITEM 1
#define TARGET_ENTITY 2
#define TARGET_POSITION 4

class Player; // fucking forward declarations :(


class Skill{
protected:
	friend class SkillTable;
	int id;
	std::string name;
	std::string description;
	SkillType type;
public:
	int getId();
	std::string getName();
	std::string getDescription();
	SkillType getType();
	unsigned char targetable;
	int (*action)(Player* p, void* target, vector<Message*>* log);
};


struct SkillValue{
	int skill;
	int level;
	int experience;
	bool tagged;
	bool raiseExperience(int amount);
};


//SKILL FUNCTIONS
int repair(Player* p, void* target, vector<Message*>* log);
int eat(Player* p, void* target, vector<Message*>* log);
int equip(Player* p, void* target, vector<Message*>* log);
int unequip(Player* p, void* target, vector<Message*>* log);


/**
[COMBAT]
pistol
shotgun
rifle
machinegun
explosives		- nades blah
unarmed			- fists of furyyyy
bludg.	melee	- baseball bats, pipes, golf clubs
edged melee 	- swords
exotic melee	- battle axes, medieval weapons 
demolitions		- tnt etc. demoing buildings safely

[PASSIVE]
survival		- make fires, tie knots etc.
running			- affects stamina while running etc
swimming		- no fatties with bathing suits plz


[ACTIVE]
traps			- 
cooking			- ability to prep food, poisin is bad mmkay
stealth			- in urban areas
woodsman		- hunting/tracking ability
construction	- ability to construct barricades etc
first aid		- hot hot murses
pharmacy		- 

*/

#endif

