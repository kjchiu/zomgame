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
	
	int maxDmg, dmg;
	MapBlock *attacker_block, *defender_block;
	attacker_block = Game::getInstance()->getMap()->getBlockAt(attacker->getLoc());
	defender_block = Game::getInstance()->getMap()->getBlockAt(targetLoc);
	//char loc[10];
	//sprintf_s(&loc[0], 10, "(%d,%d)", attacker->getLoc()->getX(), attacker->getLoc()->getY());
	
	Message* returnMessage = new Message();
	string* messageStr = new string();
	returnMessage->setMsg(messageStr);
	
	*messageStr += attacker->getName() + " attacks ";
	
	//check probability to hit based on player skill first
	if (rand() % 100 < 20){ //durr magic number 20
		*messageStr = "The zombie grabs at you but misses.";
		if (attacker->isPlayer()){
			*messageStr = attacker->getName() + " swings but misses.";  
			static_cast<Player*>(attacker)->getSkill(skill_list.getSkillID(attacker->getEquippedWeapon()->getWTypeString()))->raiseExperience(rand() % 5 + 5);
		}
		return returnMessage;
	} 
	if (attacker->isPlayer()){
		static_cast<Player*>(attacker)->getSkill(skill_list.getSkillID(attacker->getEquippedWeapon()->getWTypeString()))->raiseExperience(rand() % 10 + 5);
	}
	//TODO: subtract stamina
	//work on damage calculations and output messages
	if (attacker->getEquippedWeapon()->getName() != "fists"){
		attacker->getEquippedWeapon()->getDurability()->changeCurValueBy(-(rand()%3)-1);
	}
	
	if (defender_block->hasEntities()) {
		defender = defender_block->getTopEntity();
		*messageStr += defender_block->getTopEntity()->getName();
		if (attacker->isPlayer()){
			static_cast<Player*>(attacker)->getSkill(skill_list.getSkillID(attacker->getEquippedWeapon()->getWTypeString()))->raiseExperience(rand() % 3 + 2);
		}
	} else if (map->getBlockAt(targetLoc)->hasProps()) {
		defender = defender_block->getTopProp();
		*messageStr += defender_block->getTopProp()->getName();
		if (attacker->isPlayer()){
			static_cast<Player*>(attacker)->getSkill(skill_list.getSkillID(attacker->getEquippedWeapon()->getWTypeString()))->raiseExperience(rand() % 1 + 1);
		}
	} else {
		defender = NULL;
	}

	if (!defender) { //this means it's moved away before you can attack. Shouldn't really happen. It does.
		return NULL;
	} 

	maxDmg = 10; //zombie damage
	if (attacker->isPlayer()){maxDmg = attacker->getAttributeValue(STRENGTH) + attacker->getEquippedWeapon()->getDamage();}
	dmg = rand() % maxDmg; 
	defender->getHealth()->changeCurValueBy(-dmg);
	//points display is gay. percentile-based verbal damage output yes.
	if (dmg < maxDmg * 0.30) { *messageStr += ", but the attack barely connects."; }
	if (dmg >= maxDmg * 0.30 && dmg < maxDmg * 0.85) { *messageStr += ", connecting with a solid hit."; }
	if (dmg >= maxDmg * 0.85) { *messageStr += " and makes a powerful blow!";}
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
			Game::getInstance()->addEvent(EventFactory::createSpawnItemEvent(defender->destroy(), targetLoc, 0));
	}
	return returnMessage;
}