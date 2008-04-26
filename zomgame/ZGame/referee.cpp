#include "referee.h"

Referee::Referee(){
	
}

Message* Referee::resolveAttack(Entity* attacker, Entity* defender) {
	string message = attacker->getName();
	message += " attacks ";
	message += defender->getName();
	message += " for over 9000!";
	//subtract HP, stamina, whatever.
	return new Message(message.c_str());
}