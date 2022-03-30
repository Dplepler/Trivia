#pragma once
#include <thread>
#include <map>
#include "Server.h"
#include "Helper.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

#define START_MESSAGE "HELLO"


class Communicator {

public:

	Communicator();
	~Communicator();

	void startHandleRequests();

private:

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	//RequestHandleFactory& m_handlerFactory;

	void bindAndListen();
	SOCKET acceptClient();
	void handleNewClient(SOCKET clientSock);

};