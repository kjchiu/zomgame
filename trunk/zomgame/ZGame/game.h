#ifndef _GAME_H
#define _GAME_H

#include <deque>

#include "renderable.h"
#include "display.h"
#include "entity.h"
#include "player.h"
#include "message.h"
#include "referee.h"
#include "zombie.h"
#include "weapon.h"

class Game;
class Display;

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

	public:		
		enum Direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST};

		Game();
		Game(int tWidth, int tHeight);
		void init(int tWidth, int tHeight);
		
		Map* getMap() { return this->map;}

		void addMessage(Message* msg);
		deque<Message> getMessages();

		char* getView();
		Player* getPlayer();
		Coord* getTarget();
		void draw();
		void drawMenu();

		void moveEntity(Entity* ent, Direction dir);
		void moveTarget(Direction dir);
		void displayMapBlockInfo(MapBlock* mb);
		void dropItem(int index);
		void pickUpItem(int index);
		bool processKey(char key);
		void setCharAt(char setChar, int x, int y);
		bool isPassable(Coord* nextLoc);
		void tick();
		void run();

		//static const int WIDTH = 80, HEIGHT = 50;
		
};

#endif