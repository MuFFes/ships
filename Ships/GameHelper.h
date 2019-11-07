#pragma once
#include <string>

class GameHelper
{
	public:
		static void StandardizeCoordinatesInput(int* x, int* y);
		static bool ValidateCoordinatesInput(std::string coordinates);
};

