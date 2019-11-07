#include "GameHelper.h"
#include <iostream>
#include <string>
#include "Field.h"

using namespace std;

void GameHelper::StandardizeCoordinatesInput(int* x, int* y)
{
	if (*y < *x)
	{
		swap(*x, *y);
	}
	while (*y > 10) *y -= 16;
	while (*x > 10) *x -= 16;
	*y -= 1;
}

bool GameHelper::ValidateCoordinatesInput(string coordinates)
{
	if (coordinates.length() != 2)
	{
		return false;
	}
	if (coordinates[0] >= 48 && coordinates[0] <= 57)
	{
		if ((coordinates[1] < 65 || coordinates[1] > 74) && (coordinates[1] < 97 || coordinates[1] > 106))
		{
			return false;
		}
	}
	else if ((coordinates[0] >= 65 && coordinates[0] <= 74) || (coordinates[0] >= 97 && coordinates[0] <= 106))
	{
		if (coordinates[1] < 48 || coordinates[1] > 57)
		{
			return false;
		}
	}
	else return false;
	return true;
}
