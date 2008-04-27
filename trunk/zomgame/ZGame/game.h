#ifndef _GAME_H
#define _GAME_H

#include <deque>

#include "display.h"
#include "renderable.h"
#include "entity.h"
#include "player.h"
#include "message.h"
#include "referee.h"

class Game;
class Display;

using namespace std;

class Game {
	private:
		deque<Message> messages;
		Display* display;
		enum direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST};
		Coord* directionOffsets[8];
		Referee* ref;
		Map* map;
		Player* player;

	public:		
		Game();
		Game(int tWidth, int tHeight);
		void init(int tWidth, int tHeight);
		
		Map* getMap() { return this->map;}
		void addMessage(Message* msg);
		void draw();
		void drawMenu();
		deque<Message> getMessages();
		char* getView();
		Player* getPlayer();
		void moveEntity(Entity* ent, direction dir);
		bool processKey(char key);
		void setCharAt(char setChar, int x, int y);
		bool isPassable(Coord* nextLoc);
		void tick();
		void run();

		static const int WIDTH = 80, HEIGHT = 50;
		//CHAR_INFO world[100*100]
};


#endif