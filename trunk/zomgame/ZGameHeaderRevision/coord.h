/* A coordinate in 2D space. */

#ifndef _COORD_H
#define _COORD_H

#include <string>
#include "math.h"
#include "direction.h"

class Coord;
extern Coord DIRECTION_OFFSETS[];

using namespace std;

class Coord {
	public:
		Coord();
		Coord(int nX, int nY);
		Coord(const Coord* coord);
		Coord add(Coord& toAdd);
		int getX() const;
		int getY() const;
		Coord operator+(const Coord&) const;
		Coord operator+(const Direction&) const;
		Coord operator-(const Coord&) const;
		bool operator==(const Coord&) const;
		bool operator!=(const Coord&) const;
		int getDistance(const Coord &coord) const;
		void setCoord(const Coord* coord);
		void setX(int nX);
		void setY(int nY);
		bool equals(Coord* coord);
		string* toString();

	private:
		int x;
		int y;
};

#endif