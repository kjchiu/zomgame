#ifndef _SKILLS_H
#define _SKILLS_H

#include <string>

#include "skilltable.h"
#include "player.h"
#include "message.h"
#include "messagefactory.h"
//#include "boost/filesystem.hpp"

enum SkillType {PASSIVE, ACTIVE, INHERENT};

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
	int skill;	//corresponds to the skill table
	int level;
	int experience;
	bool tagged;	//tagged skills earn experience quicker, are determined at character creation
	bool raiseExperience(int amount);
};


//SKILL FUNCTIONS (defined in skilltable.cpp)
int repair(Player* p, void* target, vector<Message*>* log);
int eat(Player* p, void* target, vector<Message*>* log);
int equip(Player* p, void* target, vector<Message*>* log);
int unequip(Player* p, void* target, vector<Message*>* log);
int firstaid(Player* p, void* target, vector<Message*>* log);



/**
[COMBAT]
handgun - ADDED
shotgun - ADDED
rifle - ADDED
machinegun - ADDED
explosives		- nades blah -> not until we can implement explosives well
unarmed			- fists of furyyyy - ADDED
blunt melee 	- baseball bats, pipes, golf clubs - ADDED
edged melee 	- swords, daggers, pointy things - ADDED
exotic melee	- battle axes, medieval weapons? -> eh, later
demolitions		- tnt etc. demoing buildings safely -> not until explosions are added

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
first aid		- hot hot murses - ADDED
pharmacy		- if we have buffing meds (extra energy, sleep pills, etc), this ids them.

*/

#endif

