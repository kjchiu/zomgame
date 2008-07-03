#include "referee.h"

Referee::Referee(Game* game){
	this->game = game;
	srand(0);
}

int Referee::attackDirection(Entity* attacker, Direction dir) {
	Message* m = new Message();
	Coord focus = *attacker->getLoc() + *game->directionOffsets[dir];
	int time = attackLocation(attacker, &focus, m);
	//game->addMessage(m);
	return time;
}

int Referee::attackLocation(Entity* attacker, Coord* loc, Message* msg){
	string retString = "";
	MapBlock* mBlock = game->getMap()->getBlockAt(loc);
	int maxDmg = attacker->getAttribute("Strength")->getCurValue() + attacker->getEquippedWeapon()->getDamage();
	int dmg = rand() % maxDmg; 
	if (mBlock->hasEntities()){ //first, check for entities	
		mBlock->getTopEntity()->getAttribute("Health")->changeCurValueBy(-dmg);
		retString = "Attacked " + mBlock->getTopEntity()->getName();
		if (mBlock->getTopEntity()->getAttribute("Health")->getCurValue() <= 0){
			mBlock->removeEntity(mBlock->getTopEntity());	
		}
	} else if (mBlock->hasProps()){ //then, for props
		mBlock->getTopProp()->getHealth()->changeCurValueBy(-dmg); //maybe some damage resistance?
		retString = "Attacked " + mBlock->getTopProp()->getListName();
		if (mBlock->getTopProp()->getHealth()->getCurValue() <= 0){
			//loc->removeProp(loc->getTopProp());	
			destroy(mBlock->getTopProp(), loc);
		}
	} else { 
		retString = "There is nothing to attack.";
	}
			
	msg->setMsg(retString.c_str());
	return 5;
}

int Referee::attackRngLocation(Player* player, Coord* loc, Message* msg){
	char buf[128];
	Renderable* r = NULL;
	MapBlock* block;
	vector<Coord>* ray = game->getRay(player->getLoc(), loc);
	if (!ray) {
		sprintf(&buf[0], "Stop shooting yourself.");
		msg->setMsg(buf);
		return 0;
	}
	int i = 1;						
	do {
		block =	game->getMap()->getBlockAt(&(ray->at(i)));
		if (block->hasEntities()) {
			r = block->getTopEntity();
			break;
		} else if (block->hasProps()) {
			if (!block->getTopProp()->isPassable()) {
				r = block->getTopProp();
				break;
			}
		}
		i++;
	} while (i < ray->size());		

	int dur;

	// if we hit something
	if (r) {	
		if (player->getEqRngWeapon()) {
			if (block->hasEntities()) {
				// dmg prop
				static_cast<Entity*>(r)->getAttribute("Health")->changeCurValueBy(0 - player->getEqRngWeapon()->getDamage());
				// destory entity
				if (!(dur = static_cast<Entity*>(r)->getAttribute("Health")->getCurValue())) {
					destroy(block->getTopEntity(), &ray->at(i));
				}
			} else if (block->hasProps()) {
				static_cast<Prop*>(r)->getHealth()->changeCurValueBy(0 - player->getEqRngWeapon()->getDamage());
				if (!(dur = static_cast<Prop*>(r)->getHealth()->getCurValue())){
					destroy(block->getTopProp(), &ray->at(i));
				}
			}
			sprintf(&buf[0], "You shot a %s with your %s. It has %d health left.", 
							r->getName().c_str(), player->getEqRngWeapon()->getName().c_str(), dur);			
		} else {
			sprintf(&buf[0], "You point at the %s with your finger and say bang?", r->getName().c_str());
		}
	} else {
		if (player->getEqRngWeapon()) {
			sprintf(&buf[0], "You attack the darkness?");		
		} else {
			sprintf(&buf[0], "You point at the darkness with your finger and say bang?");
		}
	}
	msg->setMsg(&buf[0]);
	return 10;
}

bool Referee::doActionOnItem(Item* item, int skillIndex){
	return true;
}

bool Referee::dropItem(Entity* dropper, int index, Message* msg){
	Item* item = dropper->getInventory()->getItemAt(index);
	if (item->getType() == Item::WEAPON){	//unequip the item if the user drops it
		Weapon* weapon = (Weapon*)item;
		if (weapon == game->getPlayer()->getEqRngWeapon() || weapon == game->getPlayer()->getEquippedWeapon()){
			game->getPlayer()->unequip(weapon);
		}
	}
	dropper->getInventory()->removeItem(item);
	game->getMap()->getBlockAt(dropper->getLoc())->addItem(item);
	string message = "You dropped " + item->getListName();
	game->addMessage(new Message(&message));//msg->setMsg(message.c_str());
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
	/*char loc[10];
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
	}*/
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

int Referee::resolveEvents(DQNode* currentEvent, EventDeque* eventDeque){
	DQNode* resolvedEvent;
	while (currentEvent != NULL){
		Message* msg = currentEvent->getEventData()->resolve();
		if (msg)
			game->addMessage(msg);
		resolvedEvent = currentEvent;
		currentEvent = currentEvent->getNextNode();
		eventDeque->removeNode(resolvedEvent);
		delete resolvedEvent;
	}
	return 5;
}

int Referee::interact(Player* player, Prop* prop) {
	if (prop) {
		return prop->interact(player);
	} else {
		return 0;
	}
}

int Referee::destroy(Prop* prop, Coord* loc) {
	char msg[64];
	vector<Item*> debris = prop->destroy();
	for (int i = 0; i < debris.size(); i++) {
		sprintf(&msg[0], "added %s debris", debris.at(i)->getName().c_str());
		game->addMessage(new Message(new std::string(msg)));
		game->getMap()->getBlockAt(loc)->addItem(debris.at(i));
	}
	sprintf(&msg[0], "%s has been destroyed.", prop->getName().c_str());
	game->addMessage(new Message(new std::string(msg)));
	game->getMap()->getBlockAt(loc)->removeProp(prop);
	return 0;
}


int Referee::destroy(Entity* ent, Coord* loc) {
	Coord* newLoc = new Coord(rand() % game->getMap()->getWidth(), rand() % game->getMap()->getHeight());
	
	game->getMap()->getBlockAt(loc)->removeEntity(ent);
	ent->respawn(newLoc);
	

	return 0;
}