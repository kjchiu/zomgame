#include "skills.h"


int Skill::getId() {
	return id;
}

std::string Skill::getName() {
	return name;
}

std::string Skill::getDescription() {
	return description;
}

SkillType Skill::getType(){
	return type;
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


//1->2 = 100
//2->3 = 300
//3->4 = 600
//etc
