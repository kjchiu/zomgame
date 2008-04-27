#include <curses.h>

#include "game.h"
#include "display.h"
//bool keepPlaying = true;

//extern Game *game;
int main() {
	initscr();
	noecho();
	cbreak();
	//nodelay(stdscr, TRUE);
	int row,col;
	getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
	
	int input;
	int counter = 0;
	Game *game;
	game = new Game(); //make a new game
	game->run();
	refresh();

	endwin();
	// Exit
    return 0;
}