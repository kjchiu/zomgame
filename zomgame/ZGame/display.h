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
		bool invToggle, invSelectControl; //invSelectControl = true if the player is manipulatin the left side of the inv
		Entity* center;
		Coord* target;
		Game* game;
		int inventorySelection, minIndex, maxIndex;
		int groundSelection, minGIndex, maxGIndex;
		bool showItemDetail;

	public:
		Display(Game* game);
		virtual void init();

		Entity* getCenter();
		void setCenter(Entity* entity);
		void setTarget(Coord* target);

		void cleanSelections();
		void draw();
		void draw(Inventory* inventory);
		void draw(Map* map);	
		void draw(deque<Message> msgs);
		void drawInventoryList(vector<Item*> items, int yLoc, int selection, bool highlight);
		void dropItem();
		bool invIsToggled();
		bool processKey(int input);		
		void toggleInventory();



};

#endif