#include "referee.h"

Referee::Referee(){
	
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