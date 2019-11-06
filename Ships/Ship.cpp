#include "Ship.h"

Ship::Ship(Point start, int length, int orientation)
{
	Tiles.push_front(start);
	for (int i = 1; i < length; i++)
	{
		Point* point;
		if (orientation == 0)
			point = new Point(start.x + i, start.y);
		else
			point = new Point(start.x, start.y + i);
		Tiles.push_front(*point);
	}
}
