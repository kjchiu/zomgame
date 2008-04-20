/* A coordinate in 2D space. */

class Coord {
	public:
		Coord();
		Coord(int nX, int nY);
		int getX();
		int getY();

	private:
		int x;
		int y;
};