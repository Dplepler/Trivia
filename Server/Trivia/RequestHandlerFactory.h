#pragma once

#include "SqliteDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "GameRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "GameManager.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;


class RequestHandlerFactory
{

public:
	
	RequestHandlerFactory(IDatabase* db);
	
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);

	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room* room);

	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room* room);

	GameRequestHandler*	createGameRequestHandler(LoggedUser user, Game* game);


	LoginManager* getLoginManager() const;

	RoomManager* getRoomManager() const;

	StatisticsManager* getStatisticsManager() const;

	IDatabase* getDatabase() const;

	GameManager* getGameManager() const;
	
private:

	IDatabase* m_database;

	LoginManager* m_loginManager;

	RoomManager* m_roomManager;

	StatisticsManager* m_statisticsManager;

	GameManager* m_gameManager;
};

