#include "Server.h"

Server::Server() : m_database(new SqliteDatabase()), m_handlerFactory(m_database), m_communicator(m_handlerFactory) { }

void Server::run() {

	this->m_communicator.startHandleRequests();
}