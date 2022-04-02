#pragma once

#include "Helper.h"
#include <Windows.h>
#include <thread>
#include <exception>

#include "LoginRequestHandler.h"
#include <iostream>

#define START_MESSAGE "HELLO"

#define SERVER_PORT 8008

class Communicator {

public:

	Communicator();
	~Communicator();

	void startHandleRequests();

private:

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	void bindAndListen();
	void serverHandler();
	SOCKET acceptClient();
	void handleNewClient(SOCKET clientSock);

};