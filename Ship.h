#pragma once
#include "Point.h"

class Ship
{
	public:
		Ship(Point start = Point(), int length = 0, int direction = 0);
		const Point start;
		const int length;
		const int direction;
};

