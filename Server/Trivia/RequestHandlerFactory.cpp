#include "RequestHandlerFactory.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_database(db) { 
	this->m_loginManager = new LoginManager(db);
	this->m_roomManager = new RoomManager();
	this->m_statisticsManager = new StatisticsManager(db);
}


RequestHandlerFactory::~RequestHandlerFactory() {
	delete this->m_loginManager;
	delete this->m_roomManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() {
	return new LoginRequestHandler(this->m_database, this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user) {
	return new MenuRequestHandler(user, *this, this->m_roomManager);
}


LoginManager* RequestHandlerFactory::getLoginManager() const {
	return m_loginManager;
}

RoomManager* RequestHandlerFactory::getRoomManager() const {
	return m_roomManager;
}

IDatabase* RequestHandlerFactory::getDatabase() const {
	return this->m_database;
}

StatisticsManager* RequestHandlerFactory::getStatisticsManager() const {
	return this->m_statisticsManager;
}



