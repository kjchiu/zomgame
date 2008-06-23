#include "skills.h"

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

SkillTable::SkillTable() {
	skill_count = 0;
}	

Skill* SkillTable::getSkill(int id) {
	if (table.find(id) == table.end()){
		return NULL;
	}
	return &(table.find(id)->second);
}

/* Finds an id of a skill given. Runs in O(n), not very efficient */
int SkillTable::getSkillID(std::string skillName){
	for (int i=0; i<table.size(); i++){
		if (getSkill(i)->name == skillName){
			return table.find(i)->first;
		}
	}
	return -1;
}

void SkillTable::load(std::string filename) {
	Skill s;
	
	//PASSIVE
	s.id = skill_count++;
	s.name = "Handgun";
	s.description = "Proficiency with handguns.\nIncreases accuracy and the ability to maintain and repair them.";
	s.action = NULL;
	insert(s);

	s.id = skill_count++;
	s.name = "Blunt";
	s.description = "Proficiency with heavy, blunt weaponry.\nIncreases skill and time before breaking.";
	s.action = NULL;
	insert(s);

	//ACTIVE
	s.id = skill_count++;
	s.name = "Repair";
	s.description = "Repair an item.";
	s.action = &repair;
	insert(s);

	s.id = skill_count++;
	s.name = "Equip";
	s.description = "Equip a weapon.";
	s.action = &equip;
	insert(s);

	s.id = skill_count++;
	s.name = "Unequip";
	s.description = "Unequip a weapon.";
	s.action = &unequip;
	insert(s);

	//INHERENT
	s.id = skill_count++;
	s.name = "Consume";
	s.description = "Eat food and drink water to keep starvation from sapping your stamina.";
	s.action = &eat;
	insert(s);



	//not sure about this, requires two targets (item and mapblock)
	s.id = skill_count++;
	s.name = "Drop";
	s.description = "Drop the item onto the ground.";
//	s.action = &drop;
//	insert(s);

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

int equip(Player* p, void* target, vector<Message*>* log) {
	Weapon* weapon = static_cast<Weapon*>(target);
	p->equip(weapon);
	weapon->removeSkill(skill_list.getSkillID("Equip"));
	weapon->addSkill(skill_list.getSkillID("Unequip"));
	std::string* msg = new std::string("Equipped " + weapon->getListName());
	log->push_back(new Message(msg));
	return 0;
}

int unequip(Player* p, void* target, vector<Message*>* log) {
	Weapon* weapon = static_cast<Weapon*>(target);
	p->unequip(weapon);
	weapon->removeSkill(skill_list.getSkillID("Unequip"));
	weapon->addSkill(skill_list.getSkillID("Equip"));
	std::string* msg = new std::string("You unequipped " + weapon->getListName());
	log->push_back(new Message(msg));
	return 0;
}

/*
//same problem, need the item and a mapblock
int drop(Player* p, void* target, vector<Message*>* log) {
	Item* item = static_cast<Item*>(target);
	if (item->getType() == "Weapon"){	//unequip the item if the user drops it
		Weapon* weapon = (Weapon*)item;
		if (weapon == p->getEqRngWeapon() || weapon == p->getEquippedWeapon()){
			p->unequip(weapon);
		}
	}
	p->getInventory()->removeItem(item);
	game->getMap()->getBlockAt(dropper->getLoc())->addItem(item);
	string message = "You dropped " + item->getListName();
	msg->setMsg(message.c_str());
	return 0;
}
*/