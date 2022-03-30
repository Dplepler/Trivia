#pragma once
#include "Communicator.h"

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

#define SERVER_PORT 8008

class Server {

public:

	Server();
	void run();

private:

	//IDatabase m_database;
	Communicator m_communicator;
	//RequestHandlerFactory m_handlerFactory;

};