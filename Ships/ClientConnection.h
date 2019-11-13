#pragma once
#include "Connection.h"
#include <ws2tcpip.h>

class ClientConnection : public Connection
{
	private:
		addrinfo hints;
		addrinfo* result = nullptr;

		void initializeWinsock();
		void resolveAddress(string ip);
		void establishConnection(string ip);
	public:
		void Open(string ip) override;
		void Close() override;
		virtual ~ClientConnection();
};

