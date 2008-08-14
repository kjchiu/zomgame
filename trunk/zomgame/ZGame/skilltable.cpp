#include "skills.h"

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
	for (unsigned int i = 0; i < table.size(); i++){
		if (getSkill(i)->getName() == skillName){
			return table.find(i)->first;
		}
	}
	return -1;
}

void SkillTable::load(std::string filename) {

	
	Skill s;
	
	//PASSIVE
	s.id = skill_count++;
	s.name = "Unarmed";
	s.description = "Ability to fight with your fists. Decreases stamina loss, increases damage.";
	s.action = NULL;
	s.type = PASSIVE;
	insert(s);

	s.id = skill_count++;
	s.name = "Handgun";
	s.description = "Proficiency with handguns.\nIncreases accuracy and the ability to maintain and repair them.";
	s.action = NULL;
	s.type = PASSIVE;
	insert(s);

	s.id = skill_count++;
	s.name = "Shotgun";
	s.description = "Proficiency with multi-pellet weaponry.\nIncreases skill and time before breaking.";
	s.action = NULL;
	s.type = PASSIVE;
	insert(s);
	
	s.id = skill_count++;
	s.name = "Machine Gun";
	s.description = "Proficiency with rapid fire guns.\nIncreases skill and time before breaking.";
	s.action = NULL;
	s.type = PASSIVE;
	insert(s);
	
	s.id = skill_count++;
	s.name = "Rifle";
	s.description = "Proficiency with powerful, single-fire guns.\nIncreases skill and time before breaking.";
	s.action = NULL;
	s.type = PASSIVE;
	insert(s);

	s.id = skill_count++;
	s.name = "Blunt Melee";
	s.description = "Proficiency with heavy, blunt weaponry.\nIncreases skill and time before breaking.";
	s.action = NULL;
	s.type = PASSIVE;
	insert(s);

	s.id = skill_count++;
	s.name = "Edged Melee";
	s.description = "Proficiency with sharp and edged melee weaponry.\nIncreases skill and time before breaking.";
	s.action = NULL;
	s.type = PASSIVE;
	insert(s);

	//ACTIVE
	s.id = skill_count++;
	s.name = "Repair";
	s.description = "Repair an item.";
	s.action = &repair;
	s.type = ACTIVE;
	insert(s);

	s.id = skill_count++;
	s.name = "Equip";
	s.description = "Equip a weapon.";
	s.action = &equip;
	s.type = ACTIVE;
	insert(s);

	s.id = skill_count++;
	s.name = "Unequip";
	s.description = "Unequip a weapon.";
	s.action = &unequip;
	s.type = ACTIVE;
	insert(s);

	s.id = skill_count++;
	s.name = "First Aid";
	s.description = "Ability to treat wounds without injuring oneself. Requires equipment.";
	s.action = &firstaid;
	s.type = ACTIVE;
	insert(s);

	//INHERENT -- these skills don't level up, nor are they displayed
	s.id = skill_count++;
	s.name = "Consume";
	s.description = "Eat food and drink water to keep starvation from sapping your stamina.";
	s.action = &eat;
	s.type = INHERENT;
	insert(s);

}

void SkillTable::insert(Skill skill) {
	table.insert(std::pair<int, Skill>(skill.getId(), skill));
}


int repair(Player* p, void* target, vector<Message*>* log) {
	Weapon* weapon = static_cast<Weapon*>(target);
	//item->setBulk(item->getBulk() - 1);
	int ability = p->getSkillValue(skill_list.getSkillID("Repair"));
	
	p->getSkill(skill_list.getSkillID("Repair"))->raiseExperience(50);
	
	weapon->getDurability()->changeCurValueBy(ability*2 + 5);
	
	std::string* msg = new std::string(weapon->getName() + " has been repaired.");
	log->push_back(new Message(msg));
	return 0;
}

int eat(Player* p, void* target, vector<Message*>* log) {
	Item* item = static_cast<Item*>(target);
	item->setWeight(item->getWeight() - 1);
	if (item->getWeight() <= 0) {
		p->getInventory()->removeItem(item);
	}
	std::string* msg = new std::string("Ate " + item->getListName());
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

int firstaid(Player* p, void* target, vector<Message*>* log) {
	//target is the medical equipment being used, bandage/kit/whatever. 
	MedicalItem* medItem = static_cast<MedicalItem*>(target);
	int ability = p->getSkillValue(skill_list.getSkillID("First Aid"));
	//the more effective the tool, the higher the rate of failure. Get used to bandages!
	int chanceOfSuccess = 60 + (ability * 3) - (medItem->getHealPot() * 4);
	if ((rand() % 100) < chanceOfSuccess){
		log->push_back(new Message(new string("You healed some of your injuries.")));
		p->getSkill(skill_list.getSkillID("First Aid"))->raiseExperience(5 * medItem->getHealPot());
		p->getHealth()->changeCurValueBy(medItem->getHealPot() * 2 * ability / 3);
		//tentative formula
	} else {
		p->getSkill(skill_list.getSkillID("First Aid"))->raiseExperience(10 * medItem->getHealPot());
		log->push_back(new Message(new string("You failed to do any good.")));
	}
	
	p->getInventory()->removeItem(medItem);
	
	return 100; //note: this skill takes a long time to use, longer than 10 seconds. 10 minutes, maybe.
}