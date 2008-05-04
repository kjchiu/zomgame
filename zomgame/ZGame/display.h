/* This is the class that displays the game's information */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "game.h" 
#include "camera.h"
#include <curses.h>
#include "inventory.h"
#include "message.h"

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
		Game* game;
		int inventorySelection;
		bool showItemDetail;

	public:
		Display(Game* game);
		virtual void init();
		void draw();
		void draw(Inventory* inventory);
		void draw(Map* map);	
		void draw(deque<Message> msgs);
		void dropItem();
		bool invIsToggled();
		void processKey(int input);
		void setTarget(Entity* entity);
		void toggleInventory();
};

#endif