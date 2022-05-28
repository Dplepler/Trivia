#include "Server.h"

Server::Server() : m_database(new SqliteDatabase()), m_handlerFactory(m_database), m_communicator(m_handlerFactory) { }


Server::~Server() {
	delete m_database;
}


void Server::run() {
	this->m_communicator.startHandleRequests();
}
