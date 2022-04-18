#pragma once

#include "Helper.h"
#include <Windows.h>
#include <thread>
#include <exception>
#include <mutex>
#include <iostream>

#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"


#define START_MESSAGE "HELLO"

#define SERVER_PORT 8008

class Communicator {

public:

	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();

	void startHandleRequests();

private:

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	RequestHandlerFactory& m_handlerFactory;

	std::mutex m_clientLock;

	void bindAndListen();
	void serverHandler();
	SOCKET acceptClient();
	void handleNewClient(SOCKET clientSock);

};