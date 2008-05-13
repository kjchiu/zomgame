#ifndef _SKILLS_H
#define _SKILLS_H

#include <string>
#include <hash_map>
//#include "boost/filesystem.hpp"

enum SkillType {PASSIVE, ACTIVE};
#define TARGET_ITEM 1
#define TARGET_ENTITY 2
#define TARGET_POSITION 4


struct  Skill{
	int id;
	std::string name;
	std::string description;
	SkillType type;
	unsigned char targetable;
};

typedef std::pair<int, Skill> SkillEntry;

class SkillTable {
private:

protected:
	stdext::hash_map<int, Skill> table;
	int skill_count;
public:
	SkillTable();
	void load(std::string filename);
	Skill* getSkill(int id);
};




#endif
