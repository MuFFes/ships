#pragma once
#include "Point.h"
#include <list>

class Ship
{
	public:
		std::list<Point> Tiles;
		Ship(Point start, int length, int orientation);
		bool operator == (const Ship& s) const { return &Tiles == &s.Tiles; };
};
