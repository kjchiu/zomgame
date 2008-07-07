#include "ranged_attack_event.h"
#include "game.h"

RangedAttackEvent::RangedAttackEvent(Player *_player, Coord *_targetLoc)
: player(_player), targetLoc(_targetLoc), Event(RANGED_ATTACK) {
}

Message* RangedAttackEvent::resolve() {
	Message* msg = new Message();
	char buf[128];
	Attackable* defender = NULL;
	MapBlock* block;
	vector<Coord>* ray = Game::getInstance()->getRay(player->getLoc(), targetLoc);
	if (!ray) {
		sprintf_s(&buf[0], 128, "Stop shooting yourself.");
		msg->setMsg(buf);
		return 0;
	}

	// im an idiot and the ray list always includes the player, sigh
	unsigned int i = 1;						
	// find the first thing we hit
	do {
		block =	Game::getInstance()->getMap()->getBlockAt(&(ray->at(i)));
		if (block->hasEntities()) {
			defender = block->getTopEntity();
			break;
		} else if (block->hasProps()) {
			if (!block->getTopProp()->isPassable()) {
				defender = block->getTopProp();
				break;
			}
		}
		i++;
	} while (i < ray->size());		


	// if we hit something
	if (defender) {	
		if (player->getEqRngWeapon()) {
			// damage the defender
			defender->getHealth()->changeCurValueBy(0 - player->getEqRngWeapon()->getDamage());
			// check if it's dead
			if (!defender->getHealth()) {
				// remove entity from map
				if (block->hasEntities()) {			
					block->removeEntity(block->getTopEntity());
					defender->getHealth()->changeCurValueBy(defender->getHealth()->getMaxValue());

				} else if (block->hasProps()) {
					block->removeProp(block->getTopProp());
				}
				// add debris to map
				Game::getInstance()->addEvent(EventFactory::createSpawnItemEvent(defender->destroy(), targetLoc, 0));
				sprintf_s(&buf[0], 128, "You killed %s.", static_cast<Entity*>(defender)->getName().c_str());
			} else {	
				sprintf_s(&buf[0], 128, "You shot a %s with your %s. It has %d%% health left.", 
					static_cast<Entity*>(defender)->getName().c_str(), player->getEqRngWeapon()->getName().c_str(), defender->getHealth()->getPercentage());			
			}
		} else {
			sprintf_s(&buf[0], 128, "You have nothing to shoot with.");
		}
	} else {
		if (player->getEqRngWeapon()) {
			sprintf_s(&buf[0], 128, "You attack the darkness?");		
		} else {
			sprintf_s(&buf[0], 128, "You point at the darkness with your finger and say bang?");
		}
	}
	msg->setMsg(&buf[0]);
	return msg;
}