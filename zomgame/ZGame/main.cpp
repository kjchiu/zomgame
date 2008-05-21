#include <curses.h>

#include "game.h"
//bool keepPlaying = true;

#define DEBUG 0
//extern Game *game;

SkillTable skill_list;


int main() {
	srand(time(0));
	initscr();
	noecho();
	cbreak();
	leaveok(stdscr, false);
	curs_set(0);
	//start_color();
	keypad(stdscr, TRUE);

//	nodelay(stdscr, TRUE);
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