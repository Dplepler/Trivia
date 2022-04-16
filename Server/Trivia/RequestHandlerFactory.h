#pragma once
#include "SqliteDatabase.h"
#include "LoginRequestHandler.h"

class LoginRequestHandler;

class RequestHandlerFactory
{

public:
	
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory() = default;

	LoginRequestHandler* createLoginRequestHandler();
	
private:

	IDatabase* m_database;


};

