#pragma once
#include "Point.h"
#include "Ship.h"
#include <string>
#include <list>

using namespace std;

class Field
{
	private:
		Point *missedShots;
		Point *hitShots;
		list<Ship> ships;
	public:
		Field();
		bool AddShip(Ship* ship);
		void RemoveShip(Ship& ship);
		Ship FindShip(Point point);
		char GetState(Point point);
};

