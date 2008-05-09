#include "skills.h"

SkillTable::SkillTable() {
	skill_count = 0;
}	

Skill* SkillTable::getSkill(int id) {	
	return &(table.find(id)->second);
}

void SkillTable::load(std::string filename) {
	Skill eat;
	eat.id = skill_count;
	eat.name = "eat";
	eat.description = "eat stuff";
}

