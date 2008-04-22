#include "coord.h"

Coord::Coord(){
	x = 0;
	y = 0;
}

Coord::Coord(int nX, int nY){
	x = nX;
	y = nY;
}

Coord Coord::add(Coord &toAdd){
	return Coord(getX()+toAdd.getX(), getY()+toAdd.getY());
}

int Coord::getX() const{
	return x;
}

int Coord::getY() const{
	return y;
}

Coord Coord::operator+(const Coord& otherCoord) const {
	return Coord(getX()+otherCoord.getX(), getY()+otherCoord.getY());
}