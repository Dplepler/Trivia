#pragma once
#include "SqliteDatabase.h"
#include "LoginRequestHandler.h"
#include "LoginManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{

public:
	
	RequestHandlerFactory(IDatabase* db);
	
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();

	LoginManager* getLoginManager();

	
private:

	IDatabase* m_database;

	LoginManager* m_loginManager;


};

