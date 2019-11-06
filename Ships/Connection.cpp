#include <string>
#include "Connection.h"
#include "Exception.h"

void operator>>(Connection* const& connection, string& msg)
{
	if (!connection->isOpen)
	{
		throw Exception("Connection is closed!");
	}
	ZeroMemory(connection->recvbuf, connection->recvbuflen);
	int errCode = recv(connection->connectionSocket, connection->recvbuf, connection->recvbuflen, 0);
	if (errCode == SOCKET_ERROR) {
		errCode = WSAGetLastError();
		closesocket(connection->connectionSocket);
		throw Exception("recv error: " + to_string(errCode));
	}
	msg = std::string(connection->recvbuf);
}

void operator<<(Connection* const& connection, const string& msg)
{
	if (!connection->isOpen)
	{
		throw Exception("Connection is closed!");
	}
	if (msg.length() + 1 > DEFAULT_BUFLEN)
	{
		throw Exception("String: '" + msg + "' is too long to be sent!");
	}
	strcpy_s(connection->sendbuf, msg.c_str());
	int errCode = send(connection->connectionSocket, connection->sendbuf, connection->sendbuflen, 0);
	if (errCode == SOCKET_ERROR) {
		errCode = WSAGetLastError();
		closesocket(connection->connectionSocket);
		throw Exception("send failed with error: " + to_string(errCode));
	}
	ZeroMemory(connection->sendbuf, connection->sendbuflen);
}
