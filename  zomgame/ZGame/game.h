#ifndef GAME
#define GAME

#include <deque>

#include "player.h"
#include "message.h"

using namespace std;

class Game {
	private:
		deque<Message> messages;
		char* view;


	public:
		
		Game();
		Game(int tWidth, int tHeight);
		void init(int tWidth, int tHeight);
		
		void addMessage(Message* msg);
		deque<Message> getMessages();
		char* getView();
		void runGame();
		bool processKey(char key);
		void setCharAt(char setChar, int x, int y);
		void draw();
		void drawMenu();
		void tick();

		static const int WIDTH = 80, HEIGHT = 50;
		//CHAR_INFO world[100*100]
};

#endif