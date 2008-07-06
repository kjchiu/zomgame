#include "skill_event.h"
#include "game.h"

SkillEvent::SkillEvent(Entity* _actor, Skill* _skill, void* _target)
: actor(_actor), skill(_skill), target(_target), Event(SKILL) {
}

Message* SkillEvent::resolve() {
	std::vector<Message*> msgs;
	skill->action(static_cast<Player*>(actor), target, &msgs);
	return msgs.front();
}