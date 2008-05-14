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
	invWin = newwin(11,80,35,0); //displays the inventory
	popupWin = newwin(20, 20, 10, 30); //displays what skills can be used on an item
//	statWin;

	inventorySelection = -1;
	showItemDetail = false;
	groundSelection = -1;
	
	dState = new DisplayState();
	dState->init();

	popupSelection = 0;

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
		else {groundSelection %= groundSize; }
	if (groundSelection > maxGIndex){
		minGIndex += groundSelection - maxGIndex;
		maxGIndex += groundSelection - maxGIndex;
	} else if (groundSelection < minGIndex){
		maxGIndex -= minGIndex - groundSelection;
		minGIndex -= minGIndex - groundSelection;
	}
}

// pulls down necessary data from game to draw
void Display::draw() {
	if (!popupIsToggled()) {
		this->draw(game->getMap());
	} 
	this->draw(game->getMessages());
	if (invIsToggled()){
		this->draw(game->getPlayer()->getInventory());
	} else if (attToggle) {
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
		mvwprintw(msgWin, i+offset, 1, "> %s\n", text.c_str());
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
		dState->invSide = true;
	} 
	if (inventory->getSize() == 0){
		dState->invSide = false;
	}
	if (showItemDetail && (inventory->getSize() > 0 || groundInv.size() > 0 )){ //if the user wants to see the details of an item
		if (dState->invIsHighlighted()) { //check the inventory selection
			drawItemDetails(inventory->getItemAt(inventorySelection), height, width);	
		} else { //check the ground selection
			drawItemDetails(groundInv.at(groundSelection), height, width);
		} 	
	} else {		//otherwise, draw the full inventory
		for (int i=1; i<height-1; i++){	//draw the center column
			mvwprintw(invWin, i, width/2, "|");
		}
		drawInventoryList(inventory->getItems(), 3, inventorySelection, dState->invIsHighlighted());
		//now draw the ground items
		drawInventoryList(groundInv, width/2 + 4, groundSelection, !dState->invIsHighlighted());
	}

	//draw the skills popup if necessary
	if (popupIsToggled()) {
		drawPopup(inventory->getItemAt(inventorySelection)); 
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
	for (unsigned int i=minIndex; i<items.size() && i<=maxIndex; i++){
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

void Display::drawItemDetails(Item* item, int height, int width){
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
}

void Display::drawPopup(Item* item){
	wclear(popupWin);
	if (popupSelection < 0) {popupSelection = 0;}
	//if (popupSelection > item->getSkillsArray.size()-1) {popupSelection = item->getSkillsArray.size()-1;}
	mvwprintw(popupWin, 1,2, "%s", item->getName().c_str());
	vector<int>* skills = game->getPlayer()->getSkills();
	for (int i=0; i<maxPopupIndex; i++){
		if (i==popupSelection){
			wattron(popupWin, COLOR_PAIR(YELLOW_BLACK));
			
			mvwprintw(popupWin, i+2, 2, "-%s-", skill_list.getSkill(skills->at(i))->name.data());
			wattroff(popupWin, COLOR_PAIR(YELLOW_BLACK));
		} else {
			mvwprintw(popupWin, i+2, 3, "%s", skill_list.getSkill(skills->at(i))->name.data());
		}
	}
	box(popupWin, 0,0);
	mvwprintw(popupWin, 0, 1, "USE ITEM");
	wrefresh(popupWin);	
}

bool Display::invIsToggled(){
	return dState->invIsToggled();
}

/* Decides what context to process the key in. Returns false if no context */
bool Display::processKey(int input){
	if (popupIsToggled()){
		this->processKeyUseItem(input);
		return true;
	} else if (invIsToggled()){
		this->processKeyInventory(input);
		return true;
	}
	return false;
}

bool Display::popupIsToggled(){
	return dState->popupIsToggled();
}

bool Display::processKeyInventory(int input){
	wclear(invWin);
	if (input == 'i'){
		inventorySelection = 0;
		showItemDetail = false;
		this->toggleInventory(true);
	} else if (input == 2) { //down
		if (!showItemDetail) {
			if (dState->invIsHighlighted()){ inventorySelection += 1; }
			else {groundSelection += 1; }
			cleanSelections();
		} 
	} else if (input == 3) { //up
		if (!showItemDetail) {
			if (dState->invIsHighlighted()){ inventorySelection -= 1; }
			else {groundSelection -= 1; }
			cleanSelections();
		}
	} else if (input == 4) { //left
		dState->switchInvSelect();
	} else if (input == 5) { //right
		dState->switchInvSelect();
	} else if (input == 'd'){ //drop the item
		if (dState->invIsHighlighted()){
			game->dropItem(inventorySelection);
			cleanSelections();
		}
	} else if (input == 'g'){
		if (!dState->invIsHighlighted()){game->pickUpItem(groundSelection);} //pick up the item
	} else if (input == 10) { //enter key
		showItemDetail = !showItemDetail;
	} else if (input == 'u'){
		togglePopup();
	} else {
		return false;
	}

	return true;
}

bool Display::processKeyUseItem(int input){
	if (input == 'u'){
		togglePopup();
	} else if (input == 2) { //down
		popupSelection++; 
	} else if (input == 3) { //up
		popupSelection--;
	} else if (input == 10) { //enter
		//use the selected skill
	} else {
		return false;
	}

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

void Display::toggleInventory(bool selectedSide){
	dState->toggleInv();
	if (dState->invIsToggled()){
		minIndex = 0, maxIndex = 8; 
		minGIndex = 0, maxGIndex = 8;
		inventorySelection = groundSelection = 0;
		wresize(msgWin, 4, 80);
		mvwin(msgWin, 46,0);
	} else {
		wresize(msgWin, 15, 80);
		mvwin(msgWin, 35,0);
	}
}

void Display::toggleAttributes(){
	attToggle = !attToggle;
	if (attToggle){
		wresize(msgWin, 4, 80);
		mvwin(msgWin, 46,0);
	} else {
		wresize(msgWin, 15, 80);
		mvwin(msgWin, 35,0);
	}
}

void Display::togglePopup(){
	if (dState->invIsHighlighted() || dState->popupIsToggled()){ //can only use items you've picked up
		dState->togglePopup();
		popupSelection = 0;
	}
}

	
