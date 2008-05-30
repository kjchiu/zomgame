/* This is the class that displays the game's information */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "game.h" 
#include "camera.h"
#include <curses.h>
#include "inventory.h"
#include "message.h"
#include "globals.h"
#include "popupWin.h"

#ifndef _GAME_H_
class Game;
#endif
#ifndef _DISPLAY_H_
class Display;
#endif

struct DisplayState {
	enum State {MAPDISP, INVDISP, INVPOP, ATTR};
	State state;
	bool invSide; //true means that the player is in their inventory, false means the selection is on the ground
	void init() { state = MAPDISP; invSide = true;}
	void toggleInv() {if (state == MAPDISP){state = INVDISP; invSide=true;} else {state = MAPDISP;}}
	void togglePopup() {if (state == INVDISP && invSide == true){state = INVPOP;} else if (state == INVPOP){state = INVDISP;}}
	void switchInvSelect() { invSide = !invSide; }
	bool invIsToggled() {if (state != MAPDISP && state != ATTR){return true;} return false;}
	bool popupIsToggled() {if (state == INVPOP){return true;} return false;}
	bool invIsHighlighted() {if (state == INVDISP){ return invSide;} return false;}
	
};

class Display {
	private:
		Camera* camera;
		WINDOW* playWin;
		//WINDOW* popWin;
		WINDOW* msgWin;
		WINDOW* menuWin;
		WINDOW* invWin;
		WINDOW* skillWin;
		WINDOW* statWin;
		PopupWin* popupWin;
		bool showItemDetail; //invSelectControl = true if the player is manipulatin the left side of the inv
		Entity* center;
		Coord* target;
		Game* game;
		int inventorySelection, minIndex, maxIndex;
		int groundSelection, minGIndex, maxGIndex;
		int popupSelection, minPopupIndex, maxPopupIndex;
		bool attToggle;
		bool popupToggle;
		DisplayState* dState;
		vector<int>* skills;

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
		void draw(Player* player);
		void drawInventoryList(vector<Item*> items, int yLoc, int selection, bool highlight);
		void drawItemDetails(Item* item, int height, int width);
		void drawPopup(Item* item);	//draw the skills an item can utilize 
		bool invIsToggled();
		bool popupIsToggled();
		int processKey(int input);
		int processKeyInventory(int input);
		int processKeyUseItem(int input);
		void setUpSkillWindow(Item* item);
		void toggleInventory(bool selectedSide);
		void toggleAttributes();
		void togglePopup();

};

#endif