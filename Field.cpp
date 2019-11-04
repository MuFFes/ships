#include "Field.h"

Field::Field()
{
	missedShots = new Point[100];
	hitShots = new Point[100];
	ships = new Ship[10];
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
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < ships[i].length; j++)
		{
			if (ships[i].direction == 0)
			{
				if (ships[i].start.x + j == point.x && ships[i].start.y == point.y)
				{
					return 'X';
				}
			}
			else
			{
				if (ships[i].start.x == point.x && ships[i].start.y + j == point.y)
				{
					return 'X';
				}
			}
		}
	}
	return '.';
}
