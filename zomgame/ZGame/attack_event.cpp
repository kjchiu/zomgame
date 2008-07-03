#include "attack_event.h"
#include "game.h"

AttackEvent::AttackEvent(Entity* _attacker, Coord* _targetLoc) :
	attacker(_attacker), targetLoc(_targetLoc), Event(ATTACK){

}

Entity* AttackEvent::getAttacker(){
	return attacker;
}

Coord* AttackEvent::getTarget(){
	return targetLoc;
}

Message* AttackEvent::resolve(){
	//pretty much the code from referee, but to remove a dead entity, it'll add a REMOVE_ENT event to the queue
	Attackable* defender;
	char loc[10];
	int maxDmg, dmg;
	MapBlock *attacker_block, *defender_block;
	attacker_block = Game::getInstance()->getMap()->getBlockAt(attacker->getLoc());
	defender_block = Game::getInstance()->getMap()->getBlockAt(targetLoc);
	sprintf(&loc[0], "(%d,%d)", attacker->getLoc()->getX(), attacker->getLoc()->getY());
	Message* returnMessage = new Message();

	string* message = new string();
	*message += attacker->getName() + std::string(loc) + " attacks ";
	//check probability to hit based on player skill first
	if (rand() % 100 < 20){ //durr magic number 20
		*message += "and misses.";
		returnMessage->setMsg(message);
		return returnMessage;
	} 
	//TODO: subtract stamina
	//work on damage calculations and output messages
	attacker->getEquippedWeapon()->getDurability()->changeCurValueBy(-(rand()%3)-1);
	maxDmg = attacker->getAttribute("Strength")->getCurValue() + attacker->getEquippedWeapon()->getDamage();
	dmg = rand() % maxDmg; 

	if (defender_block->hasEntities()) {
		defender = defender_block->getTopEntity();
		*message += defender_block->getTopEntity()->getName();
	} else if (Game::getInstance()->getMap()->getBlockAt(targetLoc)->hasProps()) {
		defender = defender_block->getTopProp();
		*message += defender_block->getTopProp()->getName();
	} else {
		defender = NULL;
	}

	if (!defender) {
		return returnMessage;
	} 

	defender->getHealth()->changeCurValueBy(-dmg);
	//points display is gay. percentile-based verbal damage output yes.
	if (dmg < maxDmg/5) { *message += " with a weak strike."; }
	if (dmg >= maxDmg/5 && dmg < maxDmg/2) { *message += " with a solid hit. "; }
	if (dmg >= maxDmg/2) { *message += " with a powerful blow!";}
	defender->getHealth()->changeCurValueBy(-dmg);


	// break the weapon if it runs out of durability
	if (attacker->getEquippedWeapon()->getDurability()->getCurValue() <= 0){
		attacker->getInventory()->removeItem(attacker->getEquippedWeapon());
		attacker->equip(NULL);
	}

	// eliminate the defender
	if (defender->getHealth()->getCurValue() <= 0) {
			

		// remove defender from block
		if (Game::getInstance()->getMap()->getBlockAt(targetLoc)->hasEntities()) {			
			defender_block->removeEntity(defender_block->getTopEntity());			
		} else if (Game::getInstance()->getMap()->getBlockAt(targetLoc)->hasProps()) {
			defender_block->removeProp(defender_block->getTopProp());
		}
		std::vector<Item*> debris = defender->destroy();
		// add debris to map
		for (int i = 0; i < debris.size(); i++)
			defender_block->addItem(debris.at(i));


	}
	returnMessage->setMsg(message);
	return returnMessage;
}