#include "Server.h"

Server::Server() {

	this->m_communicator = Communicator();
}

void Server::run() {

	this->m_communicator.startHandleRequests();
}