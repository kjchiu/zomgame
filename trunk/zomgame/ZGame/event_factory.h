/* Produces events */

#ifndef _EVENT_FAC_H
#define _EVENT_FAC_H

#include "entity.h"
#include "mapblock.h"
#include "direction.h"
#include "skills.h"

class EventFactory;
class Event;
class Skill;
class Player;

class EventFactory {
	public:
		// NOTE: all tick parameters are offsets from the current tick	
		static Event* createAttackEvent(Entity* attacker, Direction dir, int tick);
		static Event* createAttackEvent(Entity* attacker, Coord* targetLoc, int tick);
		static Event* createRangedAttackEvent(Player* attacker, Coord* targetLoc, int tick);
	
		static Event* createDamageEntityEvent(Entity* entity, int damage, int tick);

		static Event* createGetItemEvent(Entity* picker, Coord* loc, int index, int tick);
		static Event* createDropItemEvent(Entity* actor, int index, int tick);

		static Event* createMoveEvent(Entity* mover, Direction dir, int tick);

		static Event* createSpawnEntityEvent(Entity* spawner, Coord* loc, int tick);
		static Event* createSpawnItemEvent(Item* spawner, Coord* loc, int tick);
		static Event* createSpawnItemEvent(std::vector<Item*> items, Coord* loc, int tick);
		static Event* createSpawnPropEvent(Prop* spawner, Coord* loc, int tick);

		static Event* createInteractEvent(Entity* actor, Coord* loc, int tick);
		static Event* createSkillEvent(Entity* actor, Skill* skill, void* target, int tick);

		static Event* createAddEffectEvent(Entity* target, Effect* effect, int tick);


};

#endif