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



chtype* Camera::getViewableArea(Map* map, Entity *target) {
	const int height = 33; //need to store these in variables
	const int width = 53; //need to store these in variables
	Deadlands dead;	
	int pX = target->getLoc()->getX();
	int pY = target->getLoc()->getY();

	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			int mapX = pX - width/2 + i;  //x position on the map
			int mapY = pY - height/2 + j; //y position on the map 
			if (mapX < 0 || mapX > width - 1 || mapY < 0 || mapY > height - 1){
				viewArea[i + (j * width)] = dead.getDisplayChar();
			} else {
				viewArea[i + (j * width)] = (map->getBlockAt(mapX, mapY))->getChar() | COLOR_PAIR(map->getBlockAt(mapX, mapY)->getColor()); 
			}
		}
	}
	return viewArea;
}
/*
MapBlock* Camera::getViewableArea(WINDOW* playWin, Map* map, Entity *target){
	const int height = 33; //need to store these in variables
	const int width = 53; //need to store these in variables
	MapBlock* viewArea = new MapBlock[height*width]; //this will be the area the player sees.
	
	for (int i =0; i<height*width; i++){
		MapBlock* m = new MapBlock();
		viewArea[i] = *m;
	}
	int pX = target->getLoc()->getX();
	int pY = target->getLoc()->getY();
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			int mapX = pX - width/2 + i;  //x position on the map
			int mapY = pY - height/2 + j; //y position on the map 
			if (mapX < 0 || mapX > width - 1 || mapY < 0 || mapY > height - 1){
				MapBlock* mb = new MapBlock();
				mb->setTerrain(new Deadlands());	//set the mapblock as "out of bounds"
				viewArea[i + (j * width)] =  *mb;
			} else {
				viewArea[i + (j * width)] = *(map->getBlockAt(mapX, mapY)); 
			}
		}
	}
	for (int x=0; x<width; x++){
		for (int y=0; y<height; y++){
			int index = x + (y * width);	
			//viewArea[index].addEntity(new Entity());
//			attron(COLOR_PAIR(viewArea[index].getColor()));

			mvwaddch(playWin, y+1, x+1, viewArea[index].getChar() |COLOR_PAIR(viewArea[index].getColor()));
		}
	}
	return viewArea;
}*/