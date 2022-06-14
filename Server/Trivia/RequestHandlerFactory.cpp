#include "RequestHandlerFactory.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_database(db) { 
	this->m_loginManager = new LoginManager(db);
	this->m_roomManager = new RoomManager();
	this->m_gameManager = new GameManager(db);
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

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room* room) {
	return new RoomAdminRequestHandler(user, *this, this->m_roomManager, room);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room* room) {
	return new RoomMemberRequestHandler(user, *this, this->m_roomManager, room);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user, Game* game) {
	return new GameRequestHandler(user, game, this->m_gameManager, *this);
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

GameManager* RequestHandlerFactory::getGameManager() const {
	return this->m_gameManager;
}

StatisticsManager* RequestHandlerFactory::getStatisticsManager() const {
	return this->m_statisticsManager;
}



