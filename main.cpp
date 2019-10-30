#include "Definitions.h"
#include <cstdio>
#include <conio.h>
#include "Exception.h"
#include "Connection.h"
#include "ServerConnection.h"
#include <iostream>
#include <ws2tcpip.h>
#include "ClientConnection.h"

int main() 
{
	try
	{
		string message;
		char c = _getch();
		if (c == 's')
		{
			Connection *connection = new ServerConnection();
			cout << "Enter port to establish connection: ";
			string port;
			cin >> port;
			connection->Open(port);
			cout << "Client connected!" << endl;
			while (message != "e")
			{
				cout << "Waiting for a message from client..." << endl;
				message = connection->Receive();
				cout << "Message from client: " << message << endl;
				cout << "Type a message to client: ";
				cin >> message;
				connection->Send(message);
				cout << "Message sent!" << endl;
			}
			cout << "Closing connection!" << endl;
			connection->Close();
			cout << "Connection closed!" << endl;
		}
		else if (c == 'c')
		{
			ClientConnection *connection = new ClientConnection();
			cout << "Enter server ip: ";
			string ip;
			cin >> ip;
			connection->Open(ip);
			cout << "Connected!" << endl;

			while (message != "e")
			{
				cout << "Type a message to server: ";
				cin >> message;
				connection->Send(message);
				cout << "Message sent: " << message << endl;
				cout << "Waiting for a message from server: ";
				message = connection->Receive();
				cout << "Message from server: ";
				cout << message << endl;
			}
			cout << "Closing connection!" << endl;
			connection->Close();
			cout << "Connection closed!" << endl;
		}
	}
	catch (Exception &ex)
	{
		cout << ex.what() << endl;
		WSACleanup();
		return 1;
	}
	char c = getchar();
    return 0;
}
