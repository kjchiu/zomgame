#include "attack_event.h"

AttackEvent::AttackEvent(Entity* nAttacker, Entity* nDefender, int tick){
	setType(Event::ATTACK);
	setAttacker(nAttacker);
	setDefender(nDefender);
	setTick(tick);
}

Entity* AttackEvent::getAttacker(){
	return attacker;
}

Entity* AttackEvent::getDefender(){
	return defender;
}

void AttackEvent::setAttacker(Entity* nAttacker){
	attacker = nAttacker;
}

void AttackEvent::setDefender(Entity *nDefender){
	defender = nDefender;
}

Message* AttackEvent::resolve(){
	//pretty much the code from referee, but to remove a dead entity, it'll add a REMOVE_ENT event to the queue
	char loc[10];
	int maxDmg, dmg;
	sprintf(&loc[0], "(%d,%d)", attacker->getLoc()->getX(), attacker->getLoc()->getY());
	Message* returnMessage = new Message();

	string* message = new string();
	*message += attacker->getName() + std::string(loc) + " attacks ";
//	if (attacker->getName() == game->getPlayer()->getName()){message = "You attack ";}
//	if (defender->getName() == game->getPlayer()->getName()){message += "you";} else {message += "the " + defender->getName();}
	//check probability to hit based on player skill first
	if (rand() % 100 < 20){ //durr magic number 20
		*message += " but the attack misses.";
	} 
	//TODO: subtract stamina
	//work on damage calculations and output messages
	attacker->getEquippedWeapon()->getDurability()->changeCurValueBy(-(rand()%3)-1);
	maxDmg = attacker->getAttribute("Strength")->getCurValue() + attacker->getEquippedWeapon()->getDamage();
	dmg = rand() % maxDmg; 
	defender->getAttribute("Health")->changeCurValueBy(-dmg);
	//points display is gay. percentile-based verbal damage output yes.
	if (dmg < maxDmg/5) { *message += " with a weak strike."; }
	if (dmg >= maxDmg/5 && dmg < maxDmg/2) { *message += " with a solid hit. "; }
	if (dmg >= maxDmg/2) { *message += " with a powerful blow!";}
	defender->getAttribute("Health")->changeCurValueBy(-dmg);

	//break the weapon if it runs out of durability
	if (attacker->getEquippedWeapon()->getDurability()->getCurValue() <= 0){
		attacker->getInventory()->removeItem(attacker->getEquippedWeapon());
		attacker->equip(NULL);
	}
	//eliminate the defender
	if (defender->getAttribute("Health")->getCurValue() <= 0) {
		//create a REMOVE_ENT event
	}
	returnMessage->setMsg(message);
	return returnMessage;
}