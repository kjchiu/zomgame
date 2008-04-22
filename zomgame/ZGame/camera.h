/* This camera class is responsible for getting the map display that the user sees */

#include <curses.h>
#include "mapblock.h"

class Camera {
	private:

	public:
		Camera();
		void drawViewableMap(WINDOW* playWin);
		MapBlock* getViewableArea();

};