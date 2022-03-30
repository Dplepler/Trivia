#pragma once
#include <thread>
#include <map>
#include <WinSock2.h>
#include <Windows.h>
#include "IRequestHandler.h"


class Communicator {

public:

	Communicator();

	void startHandleRequests();

private:

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	//RequestHandleFactory& m_handlerFactory;

	void bindAndListen();
	void handleNewClient(SOCKET clientSock);

};