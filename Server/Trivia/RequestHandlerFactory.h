#pragma once
#include "SqliteDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoginManager.h"
#include "RoomManager.h"

class LoginRequestHandler;
class MenuRequestHandler;


class RequestHandlerFactory
{

public:
	
	RequestHandlerFactory(IDatabase* db);
	
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);

	LoginManager* getLoginManager() const;

	RoomManager* getRoomManager() const;

	StatisticsManager* getStatisticsManager() const;

	IDatabase* getDatabase() const;
	
private:

	IDatabase* m_database;

	LoginManager* m_loginManager;

	RoomManager* m_roomManager;

	StatisticsManager* m_statisticsManager;


};

