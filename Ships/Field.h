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
		int GetNumberOfShips();
		bool AddShip(Ship* ship);
		void RemoveShip(Ship& ship);
		int GetNumberOfShipRemainingTiles(Ship* ship);
		int GetNumberOfRemainingTiles();
		Ship* FindShip(Point point);
		void Shoot(Point point);
		void Shoot(Point point, string state);
		char GetState(Point point);
};

