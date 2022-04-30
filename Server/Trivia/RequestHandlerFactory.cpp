#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_database(db) { 
	m_loginManager = new LoginManager(db);
	m_roomManager = new RoomManager();
}


RequestHandlerFactory::~RequestHandlerFactory() {
	delete m_loginManager;
}


LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() {
	return new LoginRequestHandler(this->m_database, this);
}


LoginManager* RequestHandlerFactory::getLoginManager() {
	return m_loginManager;
}

RoomManager* RequestHandlerFactory::getRoomManager() {
	return m_roomManager;
}

