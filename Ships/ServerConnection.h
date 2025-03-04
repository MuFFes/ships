#pragma once
#include "Connection.h"
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

class ServerConnection : public Connection
{
	private:
		SOCKET listenSocket = INVALID_SOCKET;
		addrinfo hints;
		addrinfo* result = nullptr;

		void initializeWinsock();
		void resolveAddress(string port);
		void createListenSocket();
		void setupListenSocket();
		void acceptClientSocket();
		void closeListenSocket();
	public:
		void Open(string ip) override;
		void Close() override;
		virtual ~ServerConnection();
};