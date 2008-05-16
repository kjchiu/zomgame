#include "referee.h"

Referee::Referee(Game* game){
	this->game = game;
	srand(0);
}

bool Referee::doActionOnItem(Item* item, int skillIndex){
	return true;
}

bool Referee::pickUpItem(Entity* picker, Item* item, Message* msg){
	string message = "You";//picker->getName();
	message += " picked up the ";
	message += item->getName();
	msg->setMsg(message.c_str());
	
	//check for bulk
	picker->getInventory()->addItem(item);

	return true;
}

bool Referee::resolveAttack(Entity* attacker, Entity* defender, Message* msg) {
	//subtract stamina
	string message = attacker->getName() + " attacks " + defender->getName();
	//check probability to hit based on player skill first
	if (rand() % 100 < 20){ //durr magic number 20
		message += " but misses.";
		msg->setMsg(message.c_str());	
		return false;
	} 
	int dmg = rand() % 10;
	defender->setCurHealth(defender->getCurHealth() - dmg);
	//points display is gay. percentile-based damage output yes.
	if (dmg < 3) { message += " and strikes a glancing blow."; }
	else if (dmg > 2 && dmg < 7) { message += " with a solid hit. "; }
	else if (dmg >= 7) { message += " with a powerful blow!";}
	msg->setMsg(message.c_str());
	if (defender->getCurHealth() < 0) {
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

