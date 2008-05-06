#include "camera.h"
#include "player.h"
#include "map.h"

Camera::Camera(){
	height = 33;
	width = 53;
	viewArea = new chtype[width * height];
}

void Camera::setViewableArea(int height, int width) {
	this->width = width;
	this->height = height;
	delete viewArea;
	viewArea= new chtype[width * height];
}



chtype* Camera::getViewableArea(Map* map, Entity *center) {
	const int height = 33; //need to store these in variables
	const int width = 53; //need to store these in variables
	Deadlands dead;	
	int pX = center->getLoc()->getX();
	int pY = center->getLoc()->getY();

	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			int mapX = pX - width/2 + i;  //x position on the map
			int mapY = pY - height/2 + j; //y position on the map 
			if (mapX < 0 || mapX > map->getWidth() - 1 || mapY < 0 || mapY > map->getHeight() - 1){
				viewArea[i + (j * width)] = dead.getDisplayChar();
			} else {
				viewArea[i + (j * width)] = (map->getBlockAt(mapX, mapY))->getChar() | COLOR_PAIR(map->getBlockAt(mapX, mapY)->getColor()); 
			}
		}
	}
	return viewArea;
}

Coord Camera::getLocalCoordinates(Coord* coord, Entity* center) {
	// top left = (0,0)
	// local center (width / 2, height / 2)
	int localX = coord->getX() - center->getLoc()->getX() + width / 2;
	int localY = (coord->getY() - center->getLoc()->getY()) + height / 2;
	return Coord(localX	, localY);	
}