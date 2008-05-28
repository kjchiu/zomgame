#include "referee.h"

Referee::Referee(Game* game){
	this->game = game;
	srand(0);
}

int Referee::attackLocation(Entity* attacker, MapBlock* loc, Message* msg){
	string retString = "";
	int maxDmg = attacker->getAttribute("Strength")->getCurValue() + attacker->getEquippedWeapon()->getDamage();
	int dmg = rand() % maxDmg; 
	if (loc->hasEntities()){ //first, check for entities	
		loc->getTopEntity()->getAttribute("Health")->changeCurValueBy(-dmg);
		retString = "Attacked " + loc->getTopEntity()->getName();
		if (loc->getTopEntity()->getAttribute("Health")->getCurValue() <= 0){
			loc->removeEntity(loc->getTopEntity());	
		}
	} else if (loc->hasProps()){ //then, for props
		loc->getTopProp()->getDurability()->changeCurValueBy(-dmg); //maybe some damage resistance?
		retString = "Attacked " + loc->getTopProp()->getListName();
		if (loc->getTopProp()->getDurability()->getCurValue() <= 0){
			loc->removeProp(loc->getTopProp());	
		}
	} else { 
		retString = "There is nothing to attack.";
	}
			
	msg->setMsg(retString.c_str());
	return 0;
}

bool Referee::doActionOnItem(Item* item, int skillIndex){
	return true;
}

bool Referee::dropItem(Entity* dropper, int index, Message* msg){
	Item* item = dropper->getInventory()->getItemAt(index);
	dropper->getInventory()->removeItem(item);
	game->getMap()->getBlockAt(dropper->getLoc())->addItem(item);
	string message = "You dropped " + item->getListName();
	msg->setMsg(message.c_str());
	return true;
}

bool Referee::pickUpItem(Entity* picker, MapBlock* loc, int index, Message* msg){
	if (loc->getItems().size() == 0){
		return false;
	}
	
	Item* item = loc->getItemAt(index);
	loc->removeItem(item);
	
	//check for bulk
	picker->getInventory()->addItem(item);
	string retString = "You pick up " + item->getListName();
	msg->setMsg(retString.c_str());

	return true;
}

bool Referee::resolveAttack(Entity* attacker, Entity* defender, Message* msg) {
	//subtract stamina
	string message = attacker->getName() + " attacks ";
	if (attacker->getName() == game->getPlayer()->getName()){message = "You attack ";}
	if (defender->getName() == game->getPlayer()->getName()){message += "you";} else {message += "the " + defender->getName();}
	//check probability to hit based on player skill first
	if (rand() % 100 < 20){ //durr magic number 20
		message += " but the attack misses.";
		msg->setMsg(message.c_str());	
		return false;
	} 

	//work on damage calculations and output messages
	attacker->getEquippedWeapon()->getDurability()->changeCurValueBy(-(rand()%3)-1);
	int maxDmg = attacker->getAttribute("Strength")->getCurValue() + attacker->getEquippedWeapon()->getDamage();
	int dmg = rand() % maxDmg; 
	defender->getAttribute("Health")->changeCurValueBy(-dmg);
	//points display is gay. percentile-based verbal damage output yes.
	if (dmg < maxDmg/5) { message += " with a weak strike."; }
	if (dmg >= maxDmg/5 && dmg < maxDmg/2) { message += " with a solid hit. "; }
	if (dmg >= maxDmg/2) { message += " with a powerful blow!";}
	msg->setMsg(message.c_str());
	defender->getAttribute("Health")->changeCurValueBy(-dmg);

	//break the weapon if it runs out of durability
	if (attacker->getEquippedWeapon()->getDurability()->getCurValue() <= 0){
		attacker->getInventory()->removeItem(attacker->getEquippedWeapon());
		attacker->equip(NULL);
	}
	if (defender->getAttribute("Health")->getCurValue() <= 0) {
		return true;
	}
	return false;
}

/* Performs a skill (action) on a target */
bool Referee::resolve(Player* player, void* target, int (*action)(Player*, void*, vector<Message*>*)) {	
	vector<Message*> log;
	int result =  action(player, target, &log);
	for (int i = 0; i < log.size(); i++) {
		game->addMessage(log.at(i));
	}
	//delete log;
	return result == 0;
}