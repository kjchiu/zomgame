#include "zombie.h"
#include <ctime>

Zombie::Zombie() {
	if (rand() % 3 > 1)
		color = 5;
	else 
		color = 1;
	displayChar = 'Z';
}

void Zombie::tick() {
	
}