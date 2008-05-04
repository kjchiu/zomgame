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
	inventorySelection = 0;
	showItemDetail = false;

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
}
void Display::clearLine(WINDOW* win, int start, int end, int row){
	for (int k=start; k<end; k++) {
		mvwprintw(win, row, k, " ");
	}
}

void Display::displayMessages(Game& game){
	box(msgWin, 0,0);
	deque<Message> msgs = game.getMessages();
	unsigned int max, offset = 1, windowLength; 
	getmaxyx(msgWin,max,windowLength);
	for (unsigned int i=0; i<max-2 && i<msgs.size();i++){
		string text = *(msgs.at(i)).getMsg(); //remove the pointer to avoid modifying the original message
		unsigned int cutoff = windowLength; //preserving the value of windowLength

		if (text.length() > cutoff - 6){ //chop the message in two, put on lower, and lower 'max'
			for (int j=cutoff-6; j>=0; j--){ //look for the nearest space, cut the string there
				if (text.at(j) == ' '){
					cutoff = j;
					j = 0;
				}
			}
			string secondhalf = text.substr(cutoff+1);
			
			text.resize(cutoff);
			
			clearLine(msgWin, 1, windowLength-2, (i+offset));
			mvwprintw(msgWin, i+offset++, 2, "> %s", text.c_str());
			//if (i+offset < max+2){ //TODO: Why is this not working?
				clearLine(msgWin, 1, windowLength-2, (i+offset));	
				mvwprintw(msgWin, i+offset, 2, "  %s", secondhalf.c_str());
				max--;
			//}
		} else {
			clearLine(msgWin, 1, windowLength-2, (i+offset));
			mvwprintw(msgWin, i+offset, 2, "> %s", text.c_str());	
		}
	}
	wrefresh(msgWin);
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
	// wtf magic numbers, width - 2, height - 2 to account for borders
	int height = 33;
	int width = 53;
	chtype* view = camera->getViewableArea(map, target);
	for (int x=0; x<width; x++){
		for (int y=0; y<height; y++){
			int index = x + (y * width);	
			mvwaddch(playWin, y+1, x+1, view[index]);
		}
	}
	//now display it in the play window (playWin)
	wrefresh(playWin);
	
	//check for inventory and skill, status, etc flags
	if (invToggle){
		//draw a small msg window, large invWindow
		box(invWin, 0,0);
		mvwprintw(invWin, 0, 4, "POSSESSIONS");
	
		wrefresh(invWin);
	}
	//MENU
	box(menuWin, 0,0);
	wrefresh(menuWin);
}


void Display::draw(deque<Message> msgs) {
	unsigned int height, width, offset = 1; 
	getmaxyx(msgWin,height,width);
	for (unsigned int i=0; i<height-2 && i<msgs.size();i++){
		string text = *(msgs.at(i)).getMsg(); //remove the pointer to avoid modifying the original message
		unsigned int cutoff = width; //preserving the value of windowLength
	
		clearLine(msgWin, 1, width-2, (i+offset));
		mvwprintw(msgWin, i+offset, 1, "> %s", text.c_str());
		offset += msgs.at(i).getNumLines();
	}

	//then draw the box and refresh the window
	box(msgWin, 0,0);
	wrefresh(msgWin);
}

void Display::draw(Inventory* inventory){
	wclear(invWin);
	int height, width;
	getmaxyx(invWin, height, width);
	if (inventorySelection < 0){ inventorySelection += inventory->getSize(); }
	inventorySelection %= inventory->getSize();
	if (showItemDetail){ //if the user wants to see the details of an item
		Item* item = inventory->getItemAt(inventorySelection);
		mvwprintw(invWin, 2, 3, item->getName().c_str());
		mvwprintw(invWin, 4, 5, item->getDescription().c_str());
		mvwprintw(invWin, height-2, 4, "Weight: %d lbs", item->getWeight());
		mvwprintw(invWin, height-2, width-20, "Bulk: %d", item->getBulk()); 
	} else {
		for (int i=1; i<height-1; i++){	//draw the center column
			mvwprintw(invWin, i, width/2, "|");
		}
		int xLoc = 3, yLoc = 1;
		bool nextCol = false;
		for (int i=0; i<inventory->getSize(); i++){
			string itemName = " ";
			Item* item = inventory->getItemAt(i);
			if (i == inventorySelection){
				//set current working color to be yellow on black
				wattron(invWin, COLOR_PAIR(YELLOW_BLACK));
				itemName = "-";
				itemName += item->getName().c_str();
				itemName += "-";
			} else {
				itemName += item->getName().c_str();
			}
			if (nextCol){ 
				mvwprintw(invWin,yLoc,xLoc+width/2, "%s  " , itemName.c_str());
				yLoc++;
			} else {
				mvwprintw(invWin,yLoc,xLoc, "%s  ", itemName.c_str());
			}
			nextCol = !nextCol;
			// revert back to previous color
			wattroff(invWin, COLOR_PAIR(YELLOW_BLACK));
		}
	}
}

bool Display::invIsToggled(){
	return invToggle;
}

void Display::processKey(int input){
	mvwprintw(menuWin, 4,4, "%d   ", input);
	if (input == 'i'){
		this->toggleInventory();
	} else if (input == 2) { //down
		if (!showItemDetail) {inventorySelection += 2;}
	} else if (input == 3) { //up
		if (!showItemDetail) {inventorySelection -= 2;}
	} else if (input == 4) { //left
		if (!showItemDetail) {inventorySelection -= 1;}
	} else if (input == 5) { //right
		if (!showItemDetail) {inventorySelection += 1;}
	} else if (input == 10) { //enter key
		showItemDetail = !showItemDetail;
	}
	draw();
}

void Display::setTarget(Entity* entity){
	target = entity;
}

void Display::toggleInventory(){
	invToggle = !invToggle;
	if (invToggle){
		wresize(msgWin, 4, 80);
		mvwin(msgWin, 46,0);
	} else {
		wresize(msgWin, 15, 80);
		mvwin(msgWin, 35,0);
	}
}

	