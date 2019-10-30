#pragma once
#include "Connection.h"
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

class ServerConnection : public Connection
{
	private:
		SOCKET listenSocket = INVALID_SOCKET;
		addrinfo hints;
		addrinfo* result = NULL;

		ServerConnection() {}
		ServerConnection(ServerConnection const&);
		void operator=(ServerConnection const&);

		void initializeWinsock();
		void resolveAddress();
		void createListenSocket();
		void setupListenSocket();
		void acceptClientSocket();
		void closeListenSocket();
	public:
		static ServerConnection& GetInstance();
		void Open();
		string Receive();
		void Send(string msg);
		void Close();
};
