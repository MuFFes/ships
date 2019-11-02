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
		Connection* connection = NULL;
		char myField[10][10];
		char enemyField[10][10];
		void setupFields();
		void step();
		void draw();
	public:
		Game(ServerConnection *connection);
		Game(ClientConnection *connection);
		void End();
		~Game();
};