#pragma once
#include "Communicator.h"

class Server {

public:

	Server();
	void run();

private:

	Communicator* m_communicator;

};