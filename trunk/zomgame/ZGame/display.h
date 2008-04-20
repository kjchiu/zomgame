/* This is the class that displays the game's information */

#ifndef DISPLAY
#define DISPLAY

#include "game.h" 
#include "curses.h"

class Display {
	private:
		WINDOW *playWin;
		WINDOW *msgWin;
		WINDOW *menuWin;

	public:
		Display();
		void displayMessages(Game& game);
		void draw(Game& game);	
};

#endif