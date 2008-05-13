#include "skills.h"

SkillTable::SkillTable() {
	skill_count = 0;
}	

Skill* SkillTable::getSkill(int id) {	
	return &(table.find(id)->second);
}

void SkillTable::load(std::string filename) {
	Skill s;
	s.id = skill_count;
	s.name = "eat";
	s.description = "eat stuff";
	insert(s);

	s.id = ++skill_count;
	s.name = "handgun";
	s.description = "Proficiency with handguns.\nIncreases accuracy and stuff. yay!";
	insert(s);

	s.id = ++skill_count;
	s.name = "blunt";
	s.description = "blunt melee weapons";
	insert(s);
	
}

void SkillTable::insert(Skill skill) {
	table.insert(SkillEntry(skill.id, skill));
}
