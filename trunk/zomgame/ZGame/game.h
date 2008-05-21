#ifndef _GAME_H
#define _GAME_H

#include <deque>

#include "renderable.h"
#include "display.h"
#include "entity.h"
#include "player.h"
#include "messagefactory.h"
#include "referee.h"
#include "zombie.h"
#include "weapon.h"

class Game;
class Display;
class Referee;

using namespace std;

class Game {
	private:
		deque<Message> messages;
		Display* display;
		Coord* directionOffsets[8];
		Referee* ref;
		Map* map;
		Player* player;
		Coord* target;
		vector<Zombie*> zombies;
		unsigned int tickCount;

	public:		
		enum Direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST};

		Game();
		Game(int tWidth, int tHeight);
		void init(int tWidth, int tHeight);
		
		Map* getMap() {return this->map;}
		Referee* getReferee() {return this->ref;}
		void addMessage(Message* msg);
		deque<Message> getMessages();

		char* getView();
		Player* getPlayer();
		Coord* getTarget();
		void draw();
		void drawMenu();

		void moveEntity(Entity* ent, Direction dir);
		void moveTarget(Direction dir);
		void dropItem(int index);
		void pickUpItem(int index);
		int processKey(char key);
		void setCharAt(char setChar, int x, int y);
		bool isPassable(Coord* nextLoc);
		unsigned int getTime();
		void tick();
		void run();
};

#endif