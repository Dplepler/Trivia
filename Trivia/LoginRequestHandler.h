#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{

public:

	LoginRequestHandler() = default;
	//LoginRequestHandler(LoginManager loginManager, RequestHandlerFactory factory);
	~LoginRequestHandler() = default;

	bool isRequestRelevant(RequestInfo info) const override;
	RequestResult handleRequest(RequestInfo info) override;


private:

	//LoginManager& m_loginManager;
	//RequestHandlerFactory& m_handlerFactory;

	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);


};

