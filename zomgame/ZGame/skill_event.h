/* Trigger skill effect */

#ifndef _SKILL_EVENT_H_
#define _SKILL_EVENT_H_

#include "event.h"
#include "entity.h"
#include "skills.h"

class SkillEvent : public Event {
	private:
		Entity* actor;
		Skill* skill;
		void* target;

	public:
		SkillEvent();
		SkillEvent(Entity* actor, Skill* skill, void* target);		
		Message* resolve();
};

#endif