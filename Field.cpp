#include "Field.h"

Field::Field()
{
	missedShots = new Point[100];
	hitShots = new Point[100];
}

bool Field::AddShip(Ship* ship)
{
	for (list<Point>::iterator i = ship->Tiles.begin(); i != ship->Tiles.end(); ++i)
	{
		if (i->x < 0 || i->x > 9 || i->y < 0 || i->y > 9)
		{
			return false;
		}
		for (int j = -1; j <= 1; j++)
		{
			for (int k = -1; k <= 1; k++)
			{
				if (i->x + j >= 0 && i->x + j < 10 && i->y + k >= 0 && i->y + k < 10)
					if (GetState(Point(i->x + j, i->y + k)) == 'X')
						return false;
			}
		}
	}
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
