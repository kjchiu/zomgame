#ifndef __WEAPON_FACTORY_H__
#define __WEAPON_FACTORY_H__

#include "all_includes.h"

class WeaponFactory {
public:
	static Weapon* createFists();
	static Weapon* createPistol();
};

#endif