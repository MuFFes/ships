#pragma once
#include <string>
#include "Connection.h"
#include "Field.h"

class GameHelper
{
	public:
		static void StandardizeCoordinatesInput(int* x, int* y);
		static bool ValidateCoordinatesInput(std::string coordinates);
		static void Shoot(Connection* connection, Field* enemyField);
		static void WaitForShot(Connection* connection, Field* myField);
};

