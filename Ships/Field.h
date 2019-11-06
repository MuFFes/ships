#pragma once
#include "Point.h"
#include "Ship.h"
#include <string>
#include <list>

using namespace std;

class Field
{
	private:
		list<Point> missedShots;
		list<Point> hitShots;
		list<Ship> ships;
	public:
		Field();
		bool AddShip(Ship* ship);
		//void RemoveShip(Ship& ship);
		//Ship FindShip(Point point);
		void Shoot(Point point);
		char GetState(Point point);
};

