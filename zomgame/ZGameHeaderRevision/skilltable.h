#ifndef _SKILLTABLE_H_
#define _SKILLTABLE_H_

#include "all_includes.h"

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

#endif