#include "Field.h"

Field::Field()
{

}

int Field::GetNumberOfShips()
{
	return ships.size();
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

void Field::RemoveShip(Ship& ship)
{
	ships.remove(ship);
}

Ship Field::FindShip(Point point)
{
	for (list<Ship>::iterator i = ships.begin(); i != ships.end(); ++i)
	{
		Ship s = *i;
		for (list<Point>::iterator j = s.Tiles.begin(); j != s.Tiles.end(); ++j)
		{
			if (j->x == point.x && j->y == point.y)
				return s;
		}
	}
}

void Field::Shoot(Point point)
{
	if (GetState(point) == 'X')
	{
		hitShots.push_back(point);
	}
	else
	{
		missedShots.push_back(point);
	}
}

void Field::Shoot(Point point, const string state)
{
	if (state == "42")
	{
		hitShots.push_back(point);
	}
	else
	{
		missedShots.push_back(point);
	}
}

char Field::GetState(Point point)
{
	for (list<Point>::iterator i = missedShots.begin(); i != missedShots.end(); ++i)
	{
		if (i->x == point.x && i->y == point.y)
		{
			return 'o';
		}
	}
	for (list<Point>::iterator i = hitShots.begin(); i != hitShots.end(); ++i)
	{
		if (i->x == point.x && i->y == point.y)
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
