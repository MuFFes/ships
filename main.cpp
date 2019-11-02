#include "Definitions.h"
#include <cstdio>
#include <conio.h>
#include "Exception.h"
#include "Connection.h"
#include "ServerConnection.h"
#include <iostream>
#include <ws2tcpip.h>
#include "ClientConnection.h"
#include <limits>
#include "Game.h"

int main() 
{
	try
	{
		Game *game = NULL;
		
		char c = _getch();
		if (c == 's')
		{
			ServerConnection *connection = new ServerConnection();
			cout << "Enter port to establish connection: ";
			string port;
			cin >> port;
			connection->Open(port);
			cout << "Client connected!" << endl;
			
			game = new Game(connection);
		}
		else if (c == 'c')
		{
			ClientConnection *connection = new ClientConnection();
			cout << "Enter server ip: ";
			string ip;
			cin >> ip;
			connection->Open(ip);
			cout << "Connected!" << endl;

			game = new Game(connection);
		}
		game->draw();
	}
	catch (Exception &ex)
	{
		cout << ex.what() << endl;
		WSACleanup();
		return 1;
	}
	_getch();
    return 0;
}
