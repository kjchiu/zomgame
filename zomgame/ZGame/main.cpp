#include <curses.h>

#include "game.h"
#include "globals.h"



SkillTable skill_list;
Coord DIRECTION_OFFSETS[] = {
	Coord(0,-1),
	Coord(1,-1),
	Coord(1,0),
	Coord(1, 1),
	Coord(0,1),
	Coord(-1,1),
	Coord(-1,0),
	Coord(-1,-1)
};


int main() {
	srand(static_cast<unsigned int>(time(0)));
	initscr();
	noecho();
	cbreak();
	leaveok(stdscr, false);
	curs_set(0);
	PDC_save_key_modifiers(TRUE);
	PDC_return_key_modifiers(TRUE);
	//start_color();
	keypad(stdscr, TRUE);

//	nodelay(stdscr, TRUE);
	int row,col;

	getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
	
	Game *game;
	game = Game::getInstance(); //make a new game
	game->init(100,100);
	game->run();

	refresh();

	endwin();
	// Exit
    return 0;
}