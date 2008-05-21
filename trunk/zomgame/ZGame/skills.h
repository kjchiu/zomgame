#ifndef _SKILLS_H
#define _SKILLS_H

#include <string>
#include <hash_map>
#include "player.h"
#include "message.h"
#include "messagefactory.h"
//#include "boost/filesystem.hpp"

enum SkillType {PASSIVE, ACTIVE};
#define TARGET_ITEM 1
#define TARGET_ENTITY 2
#define TARGET_POSITION 4

class Player; // fucking forward declarations :(

struct  Skill{
	int id;
	std::string name;
	std::string description;
	std::string success;
	std::string failure;
	SkillType type;
	unsigned char targetable;
	int (*action)(Player* p, void* target, vector<Message*>* log);
};


class SkillTable {
private:
	void insert(Skill skill);
protected:
	stdext::hash_map<int, Skill> table;
	int skill_count;
public:
	SkillTable();
	void load(std::string filename);
	Skill* getSkill(int id);
	int getSkillID(std::string skillName);
};

//SKILL FUNCTIONS
int repair(Player* p, void* target, vector<Message*>* log);
int eat(Player* p, void* target, vector<Message*>* log);
int equip(Player* p, void* target, vector<Message*>* log);
int unequip(Player* p, void* target, vector<Message*>* log);

#endif
