/* This is the class that displays the game's information */

#ifndef DISPLAY
#define DISPLAY

#include "game.h" 
#include "camera.h"
#include <curses.h>

#ifndef _GAME_H_
class Game;
#endif
#ifndef _DISPLAY_H_
class Display;
#endif


class Display {
	private:
		Camera* camera;
		WINDOW* playWin;
		WINDOW* msgWin;
		WINDOW* menuWin;
		WINDOW* invWin;
		WINDOW* skillWin;
		WINDOW* statWin;
		bool invToggle;
		Entity* target;
		
	public:
		Display();
		virtual void init();
		void clearLine(WINDOW* win, int start, int end, int row);
		void displayMessages(Game& game);
		void draw(Map* map);	
		//MapBlock** getViewableArea(Game& game);
		void setTarget(Entity* entity);
		void toggleInventory();
};

#endif