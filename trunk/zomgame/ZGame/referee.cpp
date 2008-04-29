#include "referee.h"

Referee::Referee(){
	
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
	string message = attacker->getName();
	message += " attacks ";
	message += defender->getName();
	message += " for over 9000!";
	//subtract HP, stamina, whatever.
	msg->setMsg(message.c_str());
	return true;
}