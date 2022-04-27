#pragma once
#include "SqliteDatabase.h"
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "RoomManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{

public:
	
	RequestHandlerFactory(IDatabase* db);
	
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();

	LoginManager* getLoginManager();

	RoomManager* getRoomManager();

	
private:

	IDatabase* m_database;

	LoginManager* m_loginManager;

	RoomManager* m_roomManager;


};

