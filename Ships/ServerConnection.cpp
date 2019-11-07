#include "ServerConnection.h"
#include "Exception.h"
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

void ServerConnection::Open(string port)
{
	initializeWinsock();
	resolveAddress(port);
	createListenSocket();
	setupListenSocket();
	acceptClientSocket();
	closeListenSocket();
	isOpen = true;
}

void ServerConnection::initializeWinsock()
{
	const int errCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (errCode)
	{
		throw Exception("WSAStartup error : " + to_string(errCode));
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
}

void ServerConnection::resolveAddress(string port)
{
	char str[7];
	strcpy_s(str, port.c_str());  
	const int errCode = getaddrinfo(NULL, str, &hints, &result);
	if (errCode)
	{
		throw Exception("getaddrinfo error : " + to_string(errCode));
	}
}

void ServerConnection::createListenSocket()
{
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == INVALID_SOCKET)
	{
		int errCode = WSAGetLastError();
		freeaddrinfo(result);
		throw Exception("socket error: " + to_string(errCode));
	}
}

void ServerConnection::setupListenSocket()
{
	int errCode = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	freeaddrinfo(result);
	
	if (errCode == SOCKET_ERROR) {
		errCode = WSAGetLastError();
		closesocket(listenSocket);
		throw Exception("bind error: " + to_string(errCode));
	}

	errCode = listen(listenSocket, SOMAXCONN);
	if (errCode == SOCKET_ERROR) {
		errCode = WSAGetLastError();
		closesocket(listenSocket);
		throw Exception("listen error: " + to_string(errCode));
	}
}

void ServerConnection::acceptClientSocket()
{
	connectionSocket = accept(listenSocket, NULL, NULL);
	if (connectionSocket == INVALID_SOCKET) 
	{
		int errCode = WSAGetLastError();
		closesocket(listenSocket);
		throw Exception("accept error: " + to_string(errCode));
	}
}

void ServerConnection::closeListenSocket()
{
	closesocket(listenSocket);
}

void ServerConnection::Close()
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
	isOpen = false;
}
