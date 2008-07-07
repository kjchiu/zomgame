#include "all_includes.h"


int Skill::getId() {
	return id;
}

std::string Skill::getName() {
	return name;
}

std::string Skill::getDescription() {
	return description;
}

/* Experience to next level = (level * 100) + ((level - 1) * 100) */
bool SkillValue::raiseExperience(int amount){
	if (level < 100){
		experience += amount;
		if (experience >= (level * 100) + ((level-1) * 100)){
			level++;
			return true;		
		}
	}
	return false;
}
