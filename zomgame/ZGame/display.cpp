#include "display.h"
#include <deque>

using namespace std;


Display::Display(Game* game) {
	init();
	this->game = game;
}

void Display::init() {
	resize_term(50,80);
	playWin = newwin(35,55,0,0); //height, width, starty, startx
	msgWin = newwin(15,80,35,0);
	menuWin = newwin(35,25,0,55);
	invWin = newwin(11,80,35,0);
	/*box(playWin, 0, 0);
	box(msgWin,0,0);
	box(menuWin,0,0);
	box(invWin,0,0);*/
//	skillWin;
//	statWin;

	invToggle = false;
	inventorySelection = -1;
	showItemDetail = false;
	groundSelection = -1;

	camera = new Camera();
	camera->setViewableArea(33, 53); //height - 2, width - 2;
	start_color();

	// TODO: we really need to move colour palette stuff somewhere else
#define DEFAULT_COLOR 0
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
#define YELLOW_BLACK 4
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);  
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
#define TARGET_COLOR COLOR_RED
#define TARGET_PAIR 6
}

/* Puts the selections within correct boundaries */
void Display::cleanSelections(){
	int invSize = game->getPlayer()->getInventory()->getSize();
	if (inventorySelection < 0){ inventorySelection += invSize; }
	if (invSize == 0){ inventorySelection = 0; }
		else { inventorySelection %= invSize; }
	if (inventorySelection > maxIndex){
		minIndex += inventorySelection - maxIndex;
		maxIndex += inventorySelection - maxIndex;
	} else if (inventorySelection < minIndex){
		maxIndex -= minIndex - inventorySelection;
		minIndex -= minIndex - inventorySelection;
	}
	
	//same for the groundSelection
	int groundSize = game->getMap()->getBlockAt(game->getPlayer()->getLoc())->getItems().size();
	if (groundSelection < 0){ groundSelection += groundSize; }
	if (groundSize == 0){ groundSelection = 0; }
		else { groundSelection %= groundSize; }
	if (groundSelection > maxGIndex){
		minGIndex += groundSelection - maxGIndex;
		maxGIndex += groundSelection - maxGIndex;
	} else if (inventorySelection < minGIndex){
		maxGIndex -= minGIndex - groundSelection;
		minGIndex -= minGIndex - groundSelection;
	}
}

// pulls down necessary data from game to draw
void Display::draw() {
	refresh();
	this->draw(game->getMap());
	this->draw(game->getMessages());
	if (invToggle){
		this->draw(game->getPlayer()->getInventory());
	}
	wrefresh(stdscr);
	refresh();
	
}

void Display::draw(Map* map) {
	//VISIBLE WORLD -- Kyle did you just make a lolcat reference? Oh my.
	box(playWin, 0,0);
	
	int height, width;
	getmaxyx(playWin,height,width);
	height -= 2;
	width -= 2;
	chtype* view = camera->getViewableArea(map, getCenter());
	Coord transTarget = camera->getLocalCoordinates(target, getCenter());
	for (int x=0; x<width; x++){
		for (int y=0; y<height; y++){
			int index = x + (y * width);	
			// if on targeted block
			// and target is no underneath player
			if (x == transTarget.getX() && y == transTarget.getY()
				&& !target->equals(getCenter()->getLoc())) {

				short fg, bg;
				// grab foreground colour of block
				pair_content(map->getBlockAt(target)->getColor(), &fg, &bg);
				// generate new pair using block fg + red bg
				init_pair(TARGET_PAIR, fg, TARGET_COLOR);
				wattron(playWin, COLOR_PAIR(TARGET_PAIR));
				mvwaddch(playWin, y+1, x+1, (char)view[index]);
				wattroff(playWin, COLOR_PAIR(TARGET_PAIR));
			} else {			
				mvwaddch(playWin, y+1, x+1, view[index]);
			}			
		}
	}
	//now display it in the play window (playWin)
	wrefresh(playWin);
	
	//MENU
	box(menuWin, 0,0);
	wrefresh(menuWin);
}


void Display::draw(deque<Message> msgs) {
	wclear(msgWin);
	unsigned int height, width, offset = 1; 
	getmaxyx(msgWin,height,width);
	for (unsigned int i=0; i<height-2 && i<msgs.size();i++){
		string text = *(msgs.at(i)).getMsg(); //remove the pointer to avoid modifying the original message
		unsigned int cutoff = width; //preserving the value of windowLength
	
	//	clearLine(msgWin, 1, width-2, (i+offset));
		mvwprintw(msgWin, i+offset, 1, "> %s", text.c_str());
		offset += msgs.at(i).getNumLines();
	}

	//then draw the box and refresh the window
	box(msgWin, 0,0);
	mvwprintw(msgWin, 0, 3, "MESSAGE LOG");
	wrefresh(msgWin);
}

void Display::draw(Inventory* inventory){
	wclear(invWin);
	int height, width;
	getmaxyx(invWin, height, width);
	vector<Item*> groundInv = game->getMap()->getBlockAt(game->getPlayer()->getLoc())->getItems();
	
	if (groundInv.empty()){
		invSelectControl = true;
	}
	if (showItemDetail && inventory->getSize() > 0){ //if the user wants to see the details of an item
		Item* item = inventory->getItemAt(inventorySelection);	
		if (!invSelectControl) {
			item = groundInv.at(groundSelection);
		} 
		mvwprintw(invWin, 2, 3, item->getName().c_str());
		mvwprintw(invWin, 4, 5, item->getDescription().c_str());
		mvwprintw(invWin, height-2, 4, "Weight: %d lbs", item->getWeight());
		mvwprintw(invWin, height-2, width-20, "Bulk: %d", item->getBulk()); 
		mvwprintw(invWin, height-2, 40, "Type: %s", item->getType().c_str());
		if (item->getType().compare("Weapon") == 0) { //display weapon stats if its a weapon
			Weapon* weapon = (Weapon*)item;
			mvwprintw(invWin, 2, width-30, "Weapon Class: %s", weapon->getWClass().c_str());
			mvwprintw(invWin, 3, width-30, "Durability: %d/%d", weapon->getCurDur(), weapon->getMaxDur());
			mvwprintw(invWin, 4, width-30, "Base Damage: %d", weapon->getDamage());

		}
	} else {		//otherwise, draw the full inventory
		for (int i=1; i<height-1; i++){	//draw the center column
			mvwprintw(invWin, i, width/2, "|");
		}
		for (int i=1; i<width; i++){
			//mvwprintw(invWin, height-3, i, "-");
		}
		drawInventoryList(inventory->getItems(), 3, inventorySelection, invSelectControl);
		//now draw the ground items
		drawInventoryList(groundInv, width/2 + 4, groundSelection, !invSelectControl);
	
	}

	
	box(invWin, 0,0);
	mvwprintw(invWin, 0, 3, "POSSESSIONS");
	mvwprintw(invWin, 0, width/2+3, "GROUND");
	wrefresh(invWin);
			
}

void Display::drawInventoryList(vector<Item*> items, int xLoc, int selection, bool highlight){
	int height, width;
	getmaxyx(invWin, height, width);

	int yLoc = 1;
	for (int i=minIndex; i<items.size() && i<=maxIndex; i++){
		string itemName = " ";
		Item* item = items.at(i);
		if (i == selection && highlight){
			//set current working color to be yellow on black
			wattron(invWin, COLOR_PAIR(YELLOW_BLACK));
			itemName = "-";
			itemName += item->getName().c_str();
			itemName += "-";
		} else {
			itemName += item->getName().c_str();
		}
		mvwprintw(invWin,yLoc,xLoc, "%s  ", itemName.c_str());
		yLoc++;
	
		// revert back to previous color
		wattroff(invWin, COLOR_PAIR(YELLOW_BLACK));
	}
}

void Display::dropItem() {
	
}

bool Display::invIsToggled(){
	return invToggle;
}

bool Display::processKey(int input){
	mvwprintw(menuWin, 4,4, "%d, %d   ", inventorySelection, groundSelection);
	if (input == 'i'){
		inventorySelection = 0;
		showItemDetail = false;
		this->toggleInventory();
	} else if (input == 2) { //down
		if (!showItemDetail) {
			if (invSelectControl){ inventorySelection += 1; }
			else {groundSelection += 1; }
			cleanSelections();
		}
	} else if (input == 3) { //up
		if (!showItemDetail) {
			if (invSelectControl){ inventorySelection -= 1; }
			else {groundSelection -= 1; }
			cleanSelections();
		}
	} else if (input == 4) { //left
		invSelectControl = !invSelectControl;
	} else if (input == 5) { //right
		invSelectControl = !invSelectControl;
	} else if (input == 'd'){ //drop the item
		if (invSelectControl){game->dropItem(inventorySelection);}
	} else if (input == 'g'){
		if (!invSelectControl){game->pickUpItem(groundSelection);} //pick up the item
	} else if (input == 10) { //enter key
		showItemDetail = !showItemDetail;
	} else {
		return false;
	}
	draw();
	return true;
}

Entity* Display::getCenter() {
	return center;
}

void Display::setCenter(Entity* newCenter){
	center = newCenter;
}

void Display::setTarget(Coord* newTarget) {
	target = newTarget;
}

void Display::toggleInventory(){
	invToggle = !invToggle;
	if (invToggle){
		minIndex = 0, maxIndex = 8; 
		minGIndex = 0, maxGIndex = 8;
		inventorySelection = groundSelection = 0;
		invSelectControl = true;
		wresize(msgWin, 4, 80);
		mvwin(msgWin, 46,0);
	} else {
		wresize(msgWin, 15, 80);
		mvwin(msgWin, 35,0);
	}
}

	