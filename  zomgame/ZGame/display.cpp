#include "display.h"
#include <deque>

using namespace std;

extern Player* player;
extern Map* map;

Display::Display() {
	playWin = newwin(35,55,0,0); //height, width, starty, startx
	msgWin = newwin(15,80,35,0);
	menuWin = newwin(35,25,0,55);
}

void Display::displayMessages(Game& game){
	deque<Message> msgs = game.getMessages();
	unsigned int max; //number of rows
	unsigned int offset = 1;
	unsigned int cLength;
	getmaxyx(msgWin,max,cLength);
	for (unsigned int i=0; i<max-2 && i<msgs.size();i++){
		Message msg = msgs.at(i);
		string text = *msg.getMsg(); //remove the pointer to avoid modifying the original message
		
		if (text.length() > cLength - 6){
			//chop the message in two, put on lower, and lower 'max'
			int cutoff = cLength - 6; //the cutoff length
			for (int j=cutoff; j>=0; j--){
				//look for the nearest space, cut the string there
				if (text.at(j) == ' '){
					cutoff = j;
					j = 0;
				}
			}
			string secondhalf = text.substr(cutoff+1);
			text.resize(cutoff);
			mvwprintw(msgWin, i+offset, 2, "> %s", text.c_str());
			offset++;
			for (int k=1; k<cLength-2; k++) {
				mvwprintw(msgWin, i+offset, k, " ");
			}	
			mvwprintw(msgWin, i+offset, 2, "  %s", secondhalf.c_str());
			
			max--;
		} else {
			for (int k=1; k<cLength-2; k++) {
				mvwprintw(msgWin, i+offset, k, " ");
			}
			mvwprintw(msgWin, i+offset, 2, "> %s", text.c_str());	
		}
	}
}

void Display::displayWorld(Game& game){
	Camera camera;
	camera.drawViewableMap(playWin);
}

void Display::draw(Game& game) {
	box(playWin, 0,0);
	//get the display area from 'game', fill in playWin with it
	displayWorld(game);
	//display will construct the view
	wrefresh(playWin);
	
	//MESSAGES
	box(msgWin, 0,0);
	displayMessages(game);
	wrefresh(msgWin); //draw any messages here via drawMsgs or something
	
	//MENU
	box(menuWin, 0,0);
	wrefresh(menuWin);
}

MapBlock* Display::getViewableArea(Game& game){
	const int height = 33; //need to store these in variables
	const int width = 53; //need to store these in variables
	MapBlock viewArea[height*width]; //this will be the area the player sees.
	return viewArea;
}