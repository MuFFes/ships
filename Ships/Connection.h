#pragma once
#include "Definitions.h"
#include <string>
#include <winsock2.h>
#include <windows.h>

using namespace std;

class Connection
{
	protected:
		WSADATA wsaData;
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;
		char sendbuf[DEFAULT_BUFLEN];
		int sendbuflen = DEFAULT_BUFLEN;
		SOCKET connectionSocket = INVALID_SOCKET;
		bool isOpen = false;
	public:
		virtual void Open(string ip) = 0;
		virtual void Close() = 0;
		virtual ~Connection() = default;
		friend void operator>>(Connection* const& connection, string& msg);
		friend void operator<<(Connection* const& connection, const string& msg);
};