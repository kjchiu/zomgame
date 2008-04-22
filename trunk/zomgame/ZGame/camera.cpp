#include "camera.h"
#include "player.h"
#include "map.h"

extern Player* player;
extern Map* map;

Camera::Camera(){

}

void Camera::drawViewableMap(WINDOW* playWin){
	int row;
	int col;
	getmaxyx(playWin,row,col);
	const int height = 33; //need to store these in variables
	const int width = 53; //need to store these in variables
	MapBlock viewArea[height*width]; //this will be the area the player sees.

	int pX = player->getLoc()->getX();
	int pY = player->getLoc()->getY();
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			int mapX = pX - width/2 + i;  //x position on the map
			int mapY = pY - height/2 + j; //y position on the map 
			if (mapX < 0 || mapX > map->MAPWIDTH - 1 || mapY < 0 || mapY > map->MAPHEIGHT - 1){
				MapBlock* mb = new MapBlock();
				mb->setTerrain(new Deadlands());
				viewArea[i + (j * width)] =  *mb;
			} else {
				viewArea[i + (j * width)] = *map->getBlockAt(mapX, mapY); 
			}
			
			//if (mapX == pX && mapY == pY){
				//MapBlock* mb = new MapBlock();
				//mb->setTerrain('@');
				//viewArea[i + (j * width)] =  *mb;
			//}
		}
	}
	//now display it in the play window (playWin)
	for (int y=0; y<width; y++){
		for (int x=0; x<height; x++){
			int index = y + (x * width);	
			//get color from viewArea[index]
			//color_set(viewArea[index].getColor(), NULL);
			//wcolor_set(playWin, COLOR_PAIR(0), NULL);
			//enable the color
			attron(COLOR_PAIR(1));

			mvwaddch(playWin, x+1, y+1, viewArea[index].getChar() | COLOR_PAIR(viewArea[index].getColor()));
			//mvwprintw(playWin, x+1,y+1, "%c", viewArea[index].getChar());
		}
	}
	
}

MapBlock* Camera::getViewableArea(){
	const int height = 33; //need to store these in variables
	const int width = 53; //need to store these in variables
	MapBlock viewArea[height*width]; //this will be the area the player sees.
	//viewMap[VIEWWIDTH/2 + (VIEWHEIGHT/2 * MAPWIDTH)].Char.UnicodeChar = '@';
	//viewmap(x,y) = map(playerX-halfway+x, playerY-halfway+y)
	int pX = player->getLoc()->getX();
	int pY = player->getLoc()->getY();
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			int mapX = pX - width/2 + i;  //x position on the map
			int mapY = pY - height/2 + j; //y position on the map 
			if (mapX < 0 || mapX > width - 1 || mapY < 0 || mapY > height - 1){
				MapBlock* mb = new MapBlock();
				mb->returnchar = '-';
				viewArea[i + (j * width)] =  *mb;
			} else {
				viewArea[i + (j * width)] = *map->getBlockAt(mapX, mapY); 
			}	
		}
	}
	return viewArea;
}