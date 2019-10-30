#include "Definitions.h"
#include <cstdio>
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
		char c = getchar();
		if (c == 's')
		{
			ServerConnection& connection = ServerConnection::GetInstance();
			cout << "Waiting for client to connect...";
			connection.Open();
			cout << "Client connected!" << endl;
			while (message != "e")
			{
				cout << "Waiting for a message from client..." << endl;
				message = connection.Receive();
				cout << "Message from client: " << message << endl;
				cout << "Type a message to client: ";
				cin >> message;
				connection.Send(message);
				cout << "Message sent!" << endl;
			}
			cout << "Closing connection!" << endl;
			connection.Close();
			cout << "Connection closed!" << endl;
		}
		else if (c == 'c')
		{
			ClientConnection& connection = ClientConnection::GetInstance();
			cout << "Connecting to server...";
			connection.Connect("127.0.0.1");
			cout << "Connected!" << endl;

			while (message != "e")
			{
				cout << "Type a message to server: ";
				cin >> message;
				connection.Send(message);
				cout << "Message sent: " << message << endl;
				cout << "Waiting for a message from server: ";
				message = connection.Receive();
				cout << "Message from server: ";
				cout << message << endl;
			}
			cout << "Closing connection!" << endl;
			connection.Close();
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
