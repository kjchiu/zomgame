#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "skills.h"
#include "player.h"
#include "coord.h"
#include "event.h"

class SkillTable;

extern SkillTable skill_list;
extern Coord DIRECTION_OFFSETS[];

void addEvent(Event* e);

#endif