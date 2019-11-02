#pragma once
#include "Connection.h"
#include <ws2tcpip.h>

class ClientConnection : public Connection
{
	private:
		addrinfo hints;
		addrinfo* result = NULL;

		void initializeWinsock();
		void resolveAddress(string ip);
		void establishConnection(string ip);
	public:
		void Open(string ip);
		string Receive();
		void Send(string msg);
		void Close();
};
