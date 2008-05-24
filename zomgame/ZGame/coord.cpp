#include "coord.h"

Coord::Coord(){
	x = 0;
	y = 0;
}

Coord::Coord(int nX, int nY){
	x = nX;
	y = nY;
}

Coord::Coord(const Coord* coord) {
	this->x = coord->getX();
	this->y = coord->getY();
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
Coord Coord::operator-(const Coord& otherCoord) const {
	return Coord(getX()-otherCoord.getX(), getY()-otherCoord.getY());
}

bool Coord::equals(Coord* coord) {
	return this->x == coord->getX() && this->y == coord->getY();
}

void Coord::setCoord(const Coord* coord) {
	this->x = coord->getX();
	this->y = coord->getY();
}

int Coord::getDistance(const Coord &coord) const {
	Coord delta = Coord(x - coord.getX(), y - coord.getY());
	return sqrt((double)(delta.getX() * delta.getX() + delta.getY() * delta.getY()));
}

string* Coord::toString(){
	string* retMsg = new string("(");
	(*retMsg) += getX();
	(*retMsg) += ", ";
	(*retMsg) += getY();
	(*retMsg) += ")";
	return retMsg;
}