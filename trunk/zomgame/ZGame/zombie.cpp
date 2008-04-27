#include "zombie.h"
#include <ctime>

Zombie::Zombie() {
	if (rand() % 3 > 1) {
		color = 5;
		displayChar = 0x151;
		setName("Uber Zombie");
	} else  {
		color = 1;
		displayChar = 'Z';
		setName("Zombie");
	}

}

void Zombie::tick() {
	
}