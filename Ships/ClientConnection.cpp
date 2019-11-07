#include "ClientConnection.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Exception.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

void ClientConnection::initializeWinsock()
{
	const int errCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (errCode)
	{
		throw Exception("WSAStartup error : " + to_string(errCode));
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

void ClientConnection::resolveAddress(string ip)
{
	char str[22], port[6];
	strcpy_s(str, ip.c_str());
	for (int i = 0; i < 30; i++)
	{
		if (str[i] == ':')
		{
			str[i] = '\0';
			strcpy_s(port, &str[i + 1]);
			break;
		}
	}
	const int errCode = getaddrinfo(str, port, &hints, &result);
	if (errCode != 0) 
	{
		throw Exception("getaddrinfo error: " + to_string(errCode));
	}
}

void ClientConnection::establishConnection(string ip)
{
	for (addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		connectionSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (connectionSocket == INVALID_SOCKET) 
		{
			throw Exception("socket error: " + to_string(WSAGetLastError()));
		}

		const int errCode = connect(connectionSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (errCode == SOCKET_ERROR) 
		{
			closesocket(connectionSocket);
			connectionSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}
	freeaddrinfo(result);

	if (connectionSocket == INVALID_SOCKET) 
	{
		throw Exception("Unable to connect to server!");
	}
}

void ClientConnection::Open(string ip)
{
	initializeWinsock();
	resolveAddress(ip);
	establishConnection(ip);
	isOpen = true;
}

void ClientConnection::Close()
{
	int errCode = shutdown(connectionSocket, SD_SEND);
	if (errCode == SOCKET_ERROR)
	{
		errCode = WSAGetLastError();
		closesocket(connectionSocket);
		throw Exception("shutdown error: " + to_string(errCode));
	}
	closesocket(connectionSocket);
	WSACleanup();
}