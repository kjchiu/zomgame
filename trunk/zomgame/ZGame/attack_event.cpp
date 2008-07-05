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
	Map* map = Game::getInstance()->getMap();
	
	Attackable* defender;
	char loc[10];
	int maxDmg, dmg;
	MapBlock *attacker_block, *defender_block;
	attacker_block = Game::getInstance()->getMap()->getBlockAt(attacker->getLoc());
	defender_block = Game::getInstance()->getMap()->getBlockAt(targetLoc);
	sprintf_s(&loc[0], 10, "(%d,%d)", attacker->getLoc()->getX(), attacker->getLoc()->getY());
	
	Message* returnMessage = new Message();
	string* messageStr = new string();
	returnMessage->setMsg(messageStr);
	
	*messageStr += attacker->getName() + std::string(loc) + " attacks ";
	//check probability to hit based on player skill first
	if (rand() % 100 < 20){ //durr magic number 20
		*messageStr += "and misses.";
		return returnMessage;
	} 
	//TODO: subtract stamina
	//work on damage calculations and output messages
	if(attacker->getEquippedWeapon()->getName() != "fists")
		attacker->getEquippedWeapon()->getDurability()->changeCurValueBy(-(rand()%3)-1);
	maxDmg = attacker->getAttribute("Strength")->getCurValue() + attacker->getEquippedWeapon()->getDamage();
	dmg = rand() % maxDmg; 

	if (defender_block->hasEntities()) {
		defender = defender_block->getTopEntity();
		*messageStr += defender_block->getTopEntity()->getName();
	} else if (map->getBlockAt(targetLoc)->hasProps()) {
		defender = defender_block->getTopProp();
		*messageStr += defender_block->getTopProp()->getName();
	} else {
		defender = NULL;
	}

	if (!defender) { //this means it's moved away before you can attack. Shouldn't really happen. It does.
		return NULL;
	} 

	defender->getHealth()->changeCurValueBy(-dmg);
	//points display is gay. percentile-based verbal damage output yes.
	if (dmg < maxDmg/5) { *messageStr += " with a weak strike."; }
	if (dmg >= maxDmg/5 && dmg < maxDmg/2) { *messageStr += " with a solid hit. "; }
	if (dmg >= maxDmg/2) { *messageStr += " with a powerful blow!";}
	defender->getHealth()->changeCurValueBy(-dmg);


	// break the weapon if it runs out of durability
	if (attacker->getEquippedWeapon()->getDurability()->getCurValue() <= 0){
		attacker->getInventory()->removeItem(attacker->getEquippedWeapon());
		attacker->equip(WeaponFactory::createFists());
	}

	// eliminate the defender
	if (defender->getHealth()->getCurValue() <= 0) {
		// remove defender from block
		if (map->getBlockAt(targetLoc)->hasEntities()) {			
			defender_block->removeEntity(defender_block->getTopEntity());
			defender->getHealth()->changeCurValueBy(defender->getHealth()->getMaxValue());

		} else if (map->getBlockAt(targetLoc)->hasProps()) {
			defender_block->removeProp(defender_block->getTopProp());
		}
		std::vector<Item*> debris = defender->destroy();
		// add debris to map
		for (unsigned int i = 0; i < debris.size(); i++)
			Game::getInstance()->addEvent(EventFactory::createSpawnItemEvent(debris.at(i), targetLoc, 0));
	}
	
	return returnMessage;
}