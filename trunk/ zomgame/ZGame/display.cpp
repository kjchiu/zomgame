#include "display.h"
#include <deque>

using namespace std;

Display::Display() {
	playWin = newwin(35,55,0,0); //height, width, starty, startx
	msgWin = newwin(15,80,35,0);
	menuWin = newwin(35,25,0,55);
}

void Display::displayMessages(Game& game){
	deque<Message> msgs = game.getMessages();
	unsigned int max = 13;
	unsigned int offset = 1;
	for (unsigned int i=0; i < max && i<msgs.size();i++){
		Message msg = msgs.at(i);
		if (msg.getMsg()->length() > 74){
			//chop the message in two, put on lower, and lower 'max'
			int cutoff = 74;
			//cut-off point is 74
			for (int j=74; j>=0; j--){
				//look for the nearest space, cut the string there
				if (msg.getMsg()->at(j) == ' '){
					cutoff = j;
					j = 0;
				}
			}
			string secondhalf = msgs.at(i).getMsg()->substr(cutoff+1);
			msg.getMsg()->resize(cutoff);
			mvwprintw(msgWin, i+offset, 2, "> %s", msg.getCharMsg());
			offset++;
			mvwprintw(msgWin, i+offset, 2, "  %s", secondhalf.c_str());
			
			max--;
		} else {
			mvwprintw(msgWin, i+offset, 2, "> %s", msgs.at(i).getCharMsg());	
		}
	}
}

void Display::draw(Game& game) {
	box(playWin, 0,0);
	//get the display area from 'game', fill in playWin with it
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