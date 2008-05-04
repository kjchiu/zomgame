#include <curses.h>

#include "game.h"
//bool keepPlaying = true;

//extern Game *game;
int main() {
	srand(time(0));
	initscr();
	noecho();
	cbreak();
	leaveok(stdscr, false);
	//start_color();
	keypad(stdscr, TRUE);

	//nodelay(stdscr, TRUE);
	int row,col;
	getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
	
	Game *game;
	game = new Game(); //make a new game
	game->run();
	refresh();

	endwin();
	// Exit
    return 0;
}