#include "referee.h"

Referee::Referee(Game* game){
	this->game = game;
	srand(0);
}

bool Referee::doActionOnItem(Item* item, int skillIndex){
	return true;
}

bool Referee::pickUpItem(Entity* picker, Item* item, Message* msg){
	string message = "You";
	message += " picked up the ";
	message += item->getName();
	msg->setMsg(message.c_str());
	
	//check for bulk
	picker->getInventory()->addItem(item);

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

bool Referee::resolve(Player* player, void* target, int (*action)(Player*, void*, vector<Message*>*)) {	
	vector<Message*> log;
	int result =  action(player, target, &log);
	for (int i = 0; i < log.size(); i++) {
		game->addMessage(log.at(i));
	}
	//delete log;
	return result == 0;
}