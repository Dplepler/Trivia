#pragma once
#include "IRequestHandler.h"
#include "SqliteDatabase.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"


class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{

public:

	LoginRequestHandler(IDatabase* db, RequestHandlerFactory* factory);
	~LoginRequestHandler() = default;

	bool isRequestRelevant(RequestInfo reqInfo) const override;
	RequestResult handleRequest(RequestInfo info) override;


private:

	RequestHandlerFactory* m_handlerFactory;

	LoginManager* m_loginManager;

	std::mutex m_loggedLock;

	RequestResult login(RequestInfo reqInfo);
	RequestResult signup(RequestInfo reqInfo);


};

