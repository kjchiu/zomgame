/* This camera class is responsible for getting the map display that the user sees */

#ifndef _CAMERA_H
#define _CAMERA_H

#include <curses.h>
#include "mapblock.h"
#include "entity.h"
#include "map.h"
#include "coord.h"

class Camera {
protected:
	chtype* viewArea;
	int width, height;
public:
	Camera();
	void setViewableArea(int height, int width);
	//return chtype buffer of viewable area.
	chtype* getViewableArea(Map* map, Entity *center);
	Coord getLocalCoordinates(Coord* coord, Entity *center);
	//MapBlock* getViewableArea(WINDOW* playWin, Map* map, Entity* target);
	
};

#endif