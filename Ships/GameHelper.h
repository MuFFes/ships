#pragma once
#include <string>
#include "Connection.h"
#include "Field.h"

class GameHelper
{
	public:
		static void StandardizeCoordinatesInput(int* x, int* y);
		static bool ValidateCoordinatesInput(std::string coordinates);
};

