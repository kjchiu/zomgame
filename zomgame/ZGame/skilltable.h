#ifndef _SKILLTABLE_H_
#define _SKILLTABLE_H_
#ifdef _GCC
	#include <ext/hash_map>
	#define stdext __gnu_cxx
#else
	#include <hash_map>
#endif
#include <string>

#include "message.h"
#include "messagefactory.h"
#include "itemfactory.h"


class Skill;

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