#include "display.h"
#include <deque>

using namespace std;

extern Player* player;
extern Map* map;

Display::Display() {
	resize_term(50,80);
	playWin = newwin(35,55,0,0); //height, width, starty, startx
	msgWin = newwin(15,80,35,0);
	menuWin = newwin(35,25,0,55);

	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_GREEN);
	init_pair(3, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
}


void Display::displayMessages(Game& game){
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
			mvwprintw(msgWin, i+offset++, 2, "> %s", text.c_str());
			if (i+offset<max-1){
				for (unsigned int k=1; k<windowLength-2; k++) {
					mvwprintw(msgWin, i+offset, k, " ");
				}	
				mvwprintw(msgWin, i+offset, 2, "  %s", secondhalf.c_str());
			}
			max--;
		} else {
			for (unsigned int k=1; k<windowLength-2; k++) {
				mvwprintw(msgWin, i+offset, k, " ");
			}
			mvwprintw(msgWin, i+offset, 2, "> %s", text.c_str());	
		}
	}
}

void Display::displayWorld(){
	Camera camera;
	camera.drawViewableMap(playWin);
}

void Display::draw(Game& game) {
	//VISIBLE WORLD
	box(playWin, 0,0);
	displayWorld(); //get the display area from 'game', fill in playWin with it
	wrefresh(playWin);
	
	//MESSAGES
	box(msgWin, 0,0);
	displayMessages(game);
	wrefresh(msgWin); 
	
	//MENU
	box(menuWin, 0,0);
	wrefresh(menuWin);
}