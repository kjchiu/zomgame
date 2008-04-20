#include <curses.h>

#include "game.h"
#include "display.h"

int main() {
	initscr();
	noecho();
	cbreak();
	//nodelay(stdscr, TRUE);
	int row,col;
	
	resize_term(50, 80);			/* force term to correct size */
	getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
	Display* display = new Display();
	bool keepPlaying = true;
	int input;
	int counter = 0;
	Game* game = new Game(); //make a new game
	refresh();
	while (keepPlaying){
		//tick, draw, until something results in quitting
		counter++;
		display->draw(*game);
		input = getch();
		keepPlaying = game->processKey(input);
	}
	endwin();
	// Exit
    return 0;
}