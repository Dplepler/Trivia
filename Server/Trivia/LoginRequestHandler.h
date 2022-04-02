#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{

public:

	LoginRequestHandler() = default;
	~LoginRequestHandler() = default;

	bool isRequestRelevant(RequestInfo info) const override;
	RequestResult handleRequest(RequestInfo info) override;


private:

	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);


};

