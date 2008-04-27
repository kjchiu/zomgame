#include "display.h"
#include <deque>

using namespace std;


Display::Display() {
	init();
}

void Display::init() {
	resize_term(50,80);
	playWin = newwin(35,55,0,0); //height, width, starty, startx
	msgWin = newwin(15,80,35,0);
	menuWin = newwin(35,25,0,55);
	invWin = newwin(12,80,35,0);
	/*box(playWin, 0, 0);
	box(msgWin,0,0);
	box(menuWin,0,0);
	box(invWin,0,0);*/
//	skillWin;
//	statWin;

	invToggle = false;

	camera = new Camera();
	camera->setViewableArea(33, 53); //height - 2, width - 2;
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
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

void Display::draw(Map* map) {
	//VISIBLE WORLD
	box(playWin, 0,0);
	// wtf magic numbers, width - 2, height - 2 to account for borders
	int height = 33;
	int width = 53;
	chtype* view = camera->getViewableArea(map, target);
	for (int x=0; x<width; x++){
		for (int y=0; y<height; y++){
			int index = x + (y * width);	
			//viewArea[index].addEntity(new Entity());
//			attron(COLOR_PAIR(viewArea[index].getColor()));

			mvwaddch(playWin, y+1, x+1, view[index]);
		}
	}
	//now display it in the play window (playWin)
	
	wrefresh(playWin);
	
	//check for inventory and skill, status, etc flags
	if (invToggle){
		//draw a small msg window, large invWindow
		//box(invWin, 0,0);
		wprintw(invWin, "Wtf");
		wrefresh(invWin);
		
		wresize(msgWin, 3, 80);
		wmove(msgWin, 0,0);
		wrefresh(msgWin);
	}
	
	// drawMessages(deque<Messages> msgs)
	//MESSAGES
	box(msgWin, 0,0);
	//displayMessages(this);
	wrefresh(msgWin); 

	//MENU
	//box(menuWin, 0,0);
	//wrefresh(menuWin);
	//wrefresh(stdscr);
	
}


void Display::draw(deque<Message> msgs) {
	box(msgWin, 0,0);
	//deque<Message> msgs = game.getMessages();
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
}
void Display::setTarget(Entity* entity){
	target = entity;
}

void Display::toggleInventory(){
	invToggle = !invToggle;
}

	