#include "GameHelper.h"
#include <iostream>

using namespace std;

void GameHelper::StandardizeCoordinatesInput(int* x, int* y)
{
	if (*y < *x)
	{
		swap(x, y);
	}
	while (*y > 10) *y -= 16;
	while (*x > 10) *x -= 16;
}
