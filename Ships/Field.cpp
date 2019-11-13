#include "Field.h"

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

int Field::GetNumberOfShipRemainingTiles(Ship* ship)
{
	int number = 0;
	for (std::list<Point>::iterator i = ship->Tiles.begin(); i != ship->Tiles.end(); ++i)
	{
		for (std::list<Point>::iterator j = hitShots.begin(); j != hitShots.end(); ++j)
		{
			if (j->x == i->x && j->y == i->y)
				number++;
		}
	}
	return ship->Tiles.size() - number;
}

int Field::GetNumberOfRemainingTiles()
{
	int number = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (GetState(Point(i, j)) == 'X')
				number++;
		}
	}
	return number;
}


Ship* Field::FindShip(Point point)
{
	for (list<Ship>::iterator i = ships.begin(); i != ships.end(); ++i)
	{
		Ship& s = *i;
		for (list<Point>::iterator j = s.Tiles.begin(); j != s.Tiles.end(); ++j)
		{
			if (j->x == point.x && j->y == point.y)
				return &s;
		}
	}
	return nullptr;
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
	if (state == "*")
	{
		hitShots.push_back(point);
	}
	else if (state == "D")
	{
		hitShots.push_back(point);
		for (int i = -1; i <= 1; i+=2)
		{
			int dist = -1;
			while (GetState(Point(point.x + (++dist * i), point.y)) == '*')
			{
				for (int j = -1; j <= 1; j++)
				{
					for (int k = -1; k <= 1; k++)
					{
						if (point.x + (dist * i) + j >= 0 && point.x + (dist * i) + j < 10 &&
							point.y + k >= 0 && point.y + k < 10)
						{
							if (GetState(Point(point.x + (dist * i) + j, point.y + k)) == '.')
							{
								missedShots.push_back(Point(point.x + (dist * i) + j, point.y + k));
							}
						}
					}
				}
			}
		}
		for (int i = -1; i <= 1; i += 2)
		{
			int dist = -1;
			while (GetState(Point(point.x, point.y + (++dist * i))) == '*')
			{
				for (int j = -1; j <= 1; j++)
				{
					for (int k = -1; k <= 1; k++)
					{
						if (point.x + j >= 0 && point.x + j < 10 &&
							point.y + (dist * i) + k >= 0 && point.y + (dist * i) + k < 10)
						{
							if (GetState(Point(point.x + j, point.y + (dist * i) + k)) == '.')
							{
								missedShots.push_back(Point(point.x + j, point.y + (dist * i) + k));
							}
						}
					}
				}
			}
		}
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
