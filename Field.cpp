#include "Field.h"

Field::Field()
{
	missedShots = new Point[100];
	hitShots = new Point[100];
}

bool Field::AddShip(Ship* ship)
{
	ships.push_front(*ship);
	return true;
}

char Field::GetState(Point point)
{
	for (int i = 0; i < 100; i++)
	{
		if (missedShots[i].x == point.x && missedShots[i].y == point.y)
		{
			return 'o';
		}
		if (hitShots[i].x == point.x && hitShots[i].y == point.y)
		{
			return '*';
		}
	}
	for (list<Ship>::iterator i = ships.begin(); i != ships.end(); ++i)
	{
		Ship s = *i;
		for (list<Point>::iterator j = s.Tiles.begin(); j != s.Tiles.end(); ++j)
		{
			if (j->x == point.x && j->y == point.y)
				return 'X';
		}
	}
	return '.';
}
