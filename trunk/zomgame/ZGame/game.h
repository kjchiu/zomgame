#ifndef GAME
#define GAME

#include <deque>

#include "player.h"
#include "message.h"
#include "entity.h"

using namespace std;

class Game {
	private:
		deque<Message> messages;
		char* view;
		enum direction {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST};
		Coord* directionOffsets[8];

	public:		
		Game();
		Game(int tWidth, int tHeight);
		void init(int tWidth, int tHeight);
		
		void addMessage(Message* msg);
		void draw();
		void drawMenu();
		deque<Message> getMessages();
		char* getView();
		void moveEntity(Entity* ent, direction dir);
		bool processKey(char key);
		void runGame();
		void setCharAt(char setChar, int x, int y);
		bool isPassable(Coord* nextLoc);
		void tick();

		static const int WIDTH = 80, HEIGHT = 50;
		//CHAR_INFO world[100*100]
};

#endif