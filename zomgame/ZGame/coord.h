/* A coordinate in 2D space. */

#ifndef _COORD_H
#define _COORD_H

#include <string>

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
		void setCoord(const Coord* coord);
		bool equals(Coord* coord);
		string* toString();

	private:
		int x;
		int y;
};

#endif