#include "weapon.h"

class WeaponFactory {
public:
	static Weapon* createFists();
	static Weapon* createPistol();
};