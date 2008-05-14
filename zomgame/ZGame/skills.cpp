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
	s.action = &eat;
	insert(s);

	s.id = ++skill_count;
	s.name = "handgun";
	s.description = "Proficiency with handguns.\nIncreases accuracy and stuff. yay!";
	s.action = NULL;
	insert(s);

	s.id = ++skill_count;
	s.name = "blunt";
	s.description = "blunt melee weapons";
	s.action = NULL;
	insert(s);

	s.id = ++skill_count;
	s.name = "repair";
	s.description = "Repair an item.";
	s.action = &repair;
	insert(s);

}

void SkillTable::insert(Skill skill) {
	table.insert(std::pair<int, Skill>(skill.id, skill));
}

int repair(Player* p, void* target, vector<Message*>* log) {
	Item* item = static_cast<Item*>(target);
	item->setBulk(item->getBulk() - 1);
	std::string* msg = new std::string(item->getName() + " has been repaired.");
	log->push_back(new Message(msg));
	return 0;
}

int eat(Player* p, void* target, vector<Message*>* log) {
	Item* item = static_cast<Item*>(target);
	item->setWeight(item->getWeight() - 1);
	if (item->getWeight() <= 0) {
		p->getInventory()->removeItem(item);
	}
	std::string* msg = new std::string("Ate a " + item->getName());
	log->push_back(new Message(msg));
	return 0;
}