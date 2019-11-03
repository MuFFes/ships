#pragma once
#include "Connection.h"
#include "ClientConnection.h"
#include "ServerConnection.h"

class Game
{
	private:
		Game();
		int isServer;
		int hasEnded = 0;
		int roundNo = 0;
		int listOfShips[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
		Connection* connection = NULL;
		char myField[10][10];
		char enemyField[10][10];
		int hasStarted;
		void clearFields();
		void setupFields();
		void step();
		void draw();
		void start();
	public:
		Game(ServerConnection *connection);
		Game(ClientConnection *connection);
		void End();
		~Game();
};