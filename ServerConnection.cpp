#include "ServerConnection.h"
#include "Exception.h"
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

ServerConnection& ServerConnection::GetInstance()
{
	static ServerConnection instance;
	return instance;
}

void ServerConnection::Open(string ip)
{
	initializeWinsock();
	resolveAddress();
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

void ServerConnection::resolveAddress()
{
	const int errCode = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
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
		freeaddrinfo(result);
		throw Exception("socket error: " + to_string(WSAGetLastError()));
	}
}

void ServerConnection::setupListenSocket()
{
	int errCode = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
	freeaddrinfo(result);
	
	if (errCode == SOCKET_ERROR) {
		closesocket(listenSocket);
		throw Exception("bind error: " + to_string(WSAGetLastError()));
	}

	errCode = listen(listenSocket, SOMAXCONN);
	if (errCode == SOCKET_ERROR) {
		closesocket(listenSocket);
		throw Exception("listen error: " + to_string(WSAGetLastError()));
	}
}

void ServerConnection::acceptClientSocket()
{
	connectionSocket = accept(listenSocket, NULL, NULL);
	if (connectionSocket == INVALID_SOCKET) 
	{
		cout << WSAGetLastError();
		closesocket(listenSocket);
		throw Exception("accept error: " + to_string(WSAGetLastError()));
	}
}

void ServerConnection::closeListenSocket()
{
	closesocket(listenSocket);
}

string ServerConnection::Receive()
{
	if (!isOpen)
	{
		throw Exception("Connection is closed!");
	}
	ZeroMemory(recvbuf, recvbuflen);
	const int errCode = recv(connectionSocket, recvbuf, recvbuflen, 0);
	if (errCode == SOCKET_ERROR) {
		closesocket(connectionSocket);
		throw Exception("recv error: " + to_string(WSAGetLastError()));
	}
	return string(recvbuf);
}

void ServerConnection::Send(string msg)
{
	if (!isOpen)
	{
		throw Exception("Connection is closed!");
	}
	if (msg.length() + 1 > DEFAULT_BUFLEN)
	{
		throw Exception("String: '" + msg + "' is too long to be sent!");
	}
	strcpy_s(sendbuf, msg.c_str());
	const int errCode = send(connectionSocket, sendbuf, sendbuflen, 0);
	if (errCode == SOCKET_ERROR) {
		closesocket(connectionSocket);
		throw Exception("send failed with error: " + to_string(WSAGetLastError()));
	}
	ZeroMemory(sendbuf, sendbuflen);
}

void ServerConnection::Close()
{
	const int errCode = shutdown(connectionSocket, SD_SEND);
	closesocket(connectionSocket);
	if (errCode == SOCKET_ERROR) 
	{
		throw Exception("shutdown error: " + to_string(WSAGetLastError()));
	}
	WSACleanup();
	isOpen = false;
}