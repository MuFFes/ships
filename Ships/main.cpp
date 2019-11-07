#include "Definitions.h"
#include <conio.h>
#include "Exception.h"
#include "Connection.h"
#include "ServerConnection.h"
#include <iostream>
#include <ws2tcpip.h>
#include "ClientConnection.h"
#include "Game.h"
#include <ctime>

int main() 
{
	try
	{
		try
		{
			Game* game = NULL;
			Connection* connection = NULL;
			string ip;
			char c;
			cout << "Press 'S' to start a server, or 'J' to join existing one!" << endl;

			do
			{
				c = _getch();
			} while (c != 's' && c != 'j' && c != 'S' && c != 'J');

			if (c == 's' || c == 'S')
			{
				connection = new ServerConnection();
				cout << "Enter port to establish connection: ";
				cin >> ip;
			}
			else if (c == 'j' || c == 'J')
			{
				connection = new ClientConnection();
				cout << "Enter server ip: ";
				cin >> ip;
			}

			connection->Open(ip);
			cout << "Connected!" << endl;
			game = new Game(connection);
			game->Start();
		}
		catch (Exception &ex)
		{
			cout << ex.what() << endl;
			WSACleanup();
			return 1;
		}
	}
	catch (exception &ex)
	{
		cout << "Unhandled exception: " << ex.what() << endl;
		return 2;
	}
	_getch();
    return 0;
}
