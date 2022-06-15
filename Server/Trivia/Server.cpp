#include "Server.h"

/* Constructor */
Server::Server() : m_database(new SqliteDatabase()), m_handlerFactory(m_database), m_communicator(m_handlerFactory) { }

/* Destructor */
Server::~Server() {
	delete m_database;
}

/* Run the server */
void Server::run() {
	this->m_communicator.startHandleRequests();
}
