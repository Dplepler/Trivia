#include "Server.h"

Server::Server() {

	this->m_communicator = new Communicator();
}

void Server::run() {

	this->m_communicator->startHandleRequests();
}