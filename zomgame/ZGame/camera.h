/* This camera class is responsible for getting the map display that the user sees */

#include <curses.h>
#include "mapblock.h"
#include "entity.h"
#include "map.h"

class Camera {
protected:
	chtype* viewArea;
	int width, height;
public:
	Camera();
	void setViewableArea(int height, int width);
	chtype* Camera::wtfViewableArea(Map* map, Entity *target);
	MapBlock* getViewableArea(WINDOW* playWin, Map* map, Entity* target);
	
};