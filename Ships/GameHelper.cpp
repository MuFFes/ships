#include "GameHelper.h"
#include <iostream>
#include "Point.h"
#include <string>
#include "Connection.h"
#include "Field.h"
#include "Exception.h"

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
	return true;
}

void GameHelper::Shoot(Connection* connection, Field* enemyField)
{
	string msg;
	int x;
	int y;
	
	cout << "Choose a tile to shoot on: ";
	bool correctData = false;
	do
	{
		cin >> msg;
		correctData = GameHelper::ValidateCoordinatesInput(msg);
		if (correctData)
		{
			x = msg[0];
			y = msg[1];
			GameHelper::StandardizeCoordinatesInput(&x, &y);
		}
		if (enemyField->GetState(Point(x, y)) != '.')
		{
			correctData = false;
			cout << "This tile had already been shot!" << endl;
		}
	} while (cout << "Enter correct coordinates:" << endl, !correctData);
	connection << to_string(x) + to_string(y);
}

void GameHelper::WaitForShot(Connection* connection, Field* myField)
{
	string msg;
	int x;
	int y;

	cout << "Waiting for your enemy to shoot...";
	connection >> msg;
	if (msg.length() == 2)
	{
		x = msg[0] - 48;
		y = msg[1] - 48;
		myField->Shoot(Point(x, y));
	}
	else throw Exception("Error receiving data from connection!");
}
