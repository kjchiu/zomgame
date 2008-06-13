#include "referee.h"

Referee::Referee(Game* game){
	this->game = game;
	srand(0);
}

int Referee::attackDirection(Entity* attacker, Direction dir) {
	Message* m = new Message();
	Coord focus = *attacker->getLoc() + *game->directionOffsets[dir];
	int time = attackLocation(attacker, game->getMap()->getBlockAt(&focus), m);
	game->addMessage(m);
	return time;
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

int Referee::attackRngLocation(Player* player, MapBlock* loc, Message* msg){
	if (loc->hasEntities()){
		if (player->getEqRngWeapon() != NULL){
			//do stuff
		}
	}
	msg->setMsg("BANG");
	return 10;
}

bool Referee::doActionOnItem(Item* item, int skillIndex){
	return true;
}

bool Referee::dropItem(Entity* dropper, int index, Message* msg){
	Item* item = dropper->getInventory()->getItemAt(index);
	if (item->getType() == "Weapon"){	//unequip the item if the user drops it
		Weapon* weapon = (Weapon*)item;
		if (weapon == game->getPlayer()->getEqRngWeapon() || weapon == game->getPlayer()->getEquippedWeapon()){
			game->getPlayer()->unequip(weapon);
		}
	}
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
	char loc[10];
	int maxDmg, dmg;
	sprintf(&loc[0], "(%d,%d)", attacker->getLoc()->getX(), attacker->getLoc()->getY());

	string message = attacker->getName() + std::string(loc) + " attacks ";
	if (attacker->getName() == game->getPlayer()->getName()){message = "You attack ";}
	if (defender->getName() == game->getPlayer()->getName()){message += "you";} else {message += "the " + defender->getName();}
	//check probability to hit based on player skill first
	if (rand() % 100 < 20){ //durr magic number 20
		message += " but the attack misses.";
		msg->setMsg(message.c_str());	
		return false;
	} 
	//TODO: subtract stamina
	//work on damage calculations and output messages
	attacker->getEquippedWeapon()->getDurability()->changeCurValueBy(-(rand()%3)-1);
	maxDmg = attacker->getAttribute("Strength")->getCurValue() + attacker->getEquippedWeapon()->getDamage();
	dmg = rand() % maxDmg; 
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
	//eliminate the defender
	if (defender->getAttribute("Health")->getCurValue() <= 0) {
		MapBlock* defenderSpace = game->getMap()->getBlockAt(defender->getLoc());
		defenderSpace->removeEntity(defender); //get rid of it
		defender->setLoc(new Coord(-2,-2));
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

int Referee::interact(Player* player, Prop* prop) {
	if (prop) {
		return prop->interact(player);
	} else {
		return 0;
	}
}