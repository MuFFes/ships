#pragma once
#include "Connection.h"
#include <ws2tcpip.h>

class ClientConnection : public Connection
{
	private:
		addrinfo hints;
		addrinfo* result = NULL;

		ClientConnection() {}
		ClientConnection(ClientConnection const&);
		void operator=(ClientConnection const&);

		void initializeWinsock();
		void resolveAddress(string ip);
		void establishConnection(string ip);
	public:
		static ClientConnection& GetInstance();
		void Connect(string ip);
		string Receive();
		void Send(string msg);
		void Close();
};
