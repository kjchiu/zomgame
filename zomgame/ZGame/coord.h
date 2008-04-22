/* A coordinate in 2D space. */

#ifndef _COORD_H
#define _COORD_H

class Coord {
	public:
		Coord();
		Coord(int nX, int nY);
		Coord add(Coord& toAdd);
		int getX() const;
		int getY() const;
		Coord operator+(const Coord&) const;
		
		
	private:
		int x;
		int y;
};

#endif