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
#include "scrollable_list.h"


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
	void toggleAttr() {if (state == MAPDISP){state = ATTR;} else {state = MAPDISP;}}
	void toggleInv() {if (state == MAPDISP){state = INVDISP; invSide=true;} else {state = MAPDISP;}}
	void togglePopup() {if (state == INVDISP && invSide == true){state = INVPOP;} else if (state == INVPOP){state = INVDISP;}}
	void switchInvSelect() { invSide = !invSide; }
	bool attrIsToggled() {if (state == ATTR){return true;} return false;}
	bool invIsToggled() {if (state != MAPDISP && state != ATTR){return true;} return false;}
	bool mapIsToggled() {if (state == MAPDISP){ return true;} return false;}
	bool popupIsToggled() {if (state == INVPOP){return true;} return false;}
	bool invIsHighlighted() {if (state == INVDISP || state == INVPOP){ return invSide;} return false;}
};

class Display {
	private:
		Camera* camera;
		WINDOW* playWin;
		WINDOW* msgWin;
		WINDOW* menuWin;
		WINDOW* invWin;
		WINDOW* skillWin;
		WINDOW* statWin;
		PopupWin* popupWin;
		
		Entity* center;
		Coord* target;
		Game* game;
		bool showItemDetail; //invSelectControl = true if the player is manipulatin the left side of the inv
		int inventorySelection, minIndex, maxIndex;
		int groundSelection, minGIndex, maxGIndex;
		int popupSelection, minPopupIndex, maxPopupIndex;
		ScrollableList* leftInv;
		ScrollableList* rightInv;
		bool attToggle;
		bool popupToggle;
		DisplayState* dState;
		vector<int>* skills;
		
		void drawInventoryList(ScrollableList* inv, int xPos, bool highlight);

	public:
		Display(Game* game);
		virtual void init();

		Entity* getCenter();
		void setCenter(Entity* entity);
		void setTarget(Coord* target);

		void cleanSelections();
		void draw();
		void draw(vector<string*>* inventoryStrings);
		void draw(Map* map);	
		void draw(deque<Message> msgs);
		void draw(Player* player, MapBlock* block);
		void drawCharacterInfo();
		void drawItemDetails(Item* item, int height, int width);
		void drawPopup(Item* item);	//draw the skills an item can utilize 
		vector<string*>* getItemStrings(vector<Item*>* itemList);
		bool gameIsActive();
		bool invIsToggled();
		bool popupIsToggled();
		int processKey(int input);
		int processKeyInventory(int input);
		int processKeyUseItem(int input);
		int processKeyAttributes(int input);
		void setUpSkillWindow(Item* item);
		void toggleInventory(bool selectedSide);
		void toggleAttributes();
		void togglePopup();

};

#endif