#pragma once
#include "Connection.h"
#include "Field.h"

class Game
{
	private:
		int priority = 0;
		int enemyPriority = 0;
		int hasEnded = 0;
		int isWinner = 0;
		int listOfShips[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
		Connection* connection = NULL;
		Field myField;
		Field enemyField;
		void shoot();
		void waitForShot();
		void setupFields();
		void step();
		void draw();
		void end();
	public:
		Game(Connection *connection);
		void Start();
		~Game();
};
