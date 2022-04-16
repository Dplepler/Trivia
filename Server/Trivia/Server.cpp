#include "Server.h"

Server::Server() : m_database(new SqliteDatabase()), m_communicator(Communicator(m_handlerFactory)), m_handlerFactory(RequestHandlerFactory(m_database)) { }

void Server::run() {

	this->m_communicator.startHandleRequests();
}