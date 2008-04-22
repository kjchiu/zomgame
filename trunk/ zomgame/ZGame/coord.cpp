#include "coord.h"

Coord::Coord(){
	x = 0;
	y = 0;
}

Coord::Coord(int nX, int nY){
	x = nX;
	y = nY;
}

int Coord::getX(){
	return x;
}

int Coord::getY(){
	return y;
}